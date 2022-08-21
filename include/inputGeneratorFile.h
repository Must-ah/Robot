#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H
#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <coroutine>
using std::suspend_always;

//#include<new>
#include <utility>

#include <fstream>

template <typename T, typename G>
struct promise_type_base
{
    T mValue;

    auto yield_value(T value)
    {
        mValue = std::move(value);
        return suspend_always{};
    }
    G get_return_object() { return G{this}; };

    suspend_always initial_suspend() { return {}; }
    suspend_always final_suspend() noexcept { return {}; }

    void return_void() {}
    void unhandled_exception()
    {
        std::terminate();
    }
    static auto get_return_object_on_allocation_failure()
    {
        return G{nullptr};
    }
};

namespace coro_iterator
{
    template <typename PT>
    struct iterator
    {
        std::coroutine_handle<PT> mCoroHdl{nullptr};

        void resume()
        {
            if (not mCoroHdl.done())
            {
                mCoroHdl.resume();
            }
        }

        iterator() = default;
        iterator(std::coroutine_handle<PT> hco) : mCoroHdl{hco}
        {
            resume();
        }
        void operator++() { resume(); }
        bool operator==(const iterator &) const
        {
            return mCoroHdl.done();
        }
        const auto &operator*() const
        {
            return mCoroHdl.promise().mValue;
        }
    };
} // namespace coro_iterator

template <typename T>
struct generator
{
    using promise_type =
        promise_type_base<T, generator>;
    using PromiseTypeHandle = std::coroutine_handle<promise_type>;

    using iterator = coro_iterator::iterator<promise_type>;
    iterator begin() { return {mCoroHdl}; }
    iterator end() { return {}; }

    generator(generator const &) = delete;
    generator(generator &&rhs) : mCoroHdl(std::exchange(rhs.mCoroHdl, nullptr))
    {
    }

    ~generator()
    {
        if (mCoroHdl)
        {
            mCoroHdl.destroy();
        }
    }

private:
    friend promise_type;
    explicit generator(promise_type *p)
        : mCoroHdl{PromiseTypeHandle::from_promise(*p)}
    {
    }

    PromiseTypeHandle mCoroHdl;
};

using StringGenerator = generator<string>;

StringGenerator fileOpener(const string &filename)
{
    std::ifstream file;
    file.open(filename);
    if (file.is_open())
    {
        string line = "";
        while (!file.eof())
        {
            std::getline(file, line);
            co_yield line;
        }
    }
    else
    {
        cout << "File not found" << endl;
    }
}
/*
void readFromFile(string filePath)
{
    // cout << "Reading from file: " << filePath << endl;
    for (auto line : fileOpener(filePath))
    {
        cout << line << endl;
    }
}
*/

/*
int main()
{
    UseCounter();
    readFromFile("./data/input.txt");
    return 0;
}
*/

#endif // FILE_GENERATOR_H