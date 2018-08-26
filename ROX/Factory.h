#pragma once
#include <string>
#include <map>
#include <functional>
#include <memory>



template <typename T>
using SPTR = std::shared_ptr<T>;

template <typename T>
using WPTR = std::weak_ptr<T>;

template <typename T>
using UPTR = std::unique_ptr<T>;


class IBase
{
public:
    virtual ~IBase() {};

    virtual void Foo() {};

private:

};

class IBase2
{
public:
    virtual ~IBase2() {}
    virtual void Foo2() {}
private:

};

template <typename Base>
class Factory
{
public:
    typedef std::string KEY;

    template <typename Base>
    using CONSTRUCT = std::function<Base*(void)>;

    template <typename Base>
    using MAP_KEY_GENERATOR = std::map<KEY, CONSTRUCT<Base>>;

    Factory()
    {

    }

    ~Factory()
    {
    }

    template<typename Inherit>
    struct Register_t
    {
        Register_t(const KEY& key)
        {
            Factory<Base>::Get()._mapFunc.emplace(key, [] {return new Inherit(); });
        }

        template<typename...Args>
        Register_t(const KEY& key, Args...args)
        {
            Factory<Base>::Get()._mapFunc.emplace(key, [=] {return new Inherit(args...); });
        }

    };

    void Register(const KEY key,const Factory<Base>::CONSTRUCT<Base>& constrct)
    {
        Factory<Base>::Get()._mapFunc.emplace(key, constrct);
    }

    static Base* produce(const KEY& key)
    {
        if (_mapFunc.find(key) == _mapFunc.end())
        {
            return nullptr;
        }

        return _mapFunc[key]();
    }

    static SPTR<Base> produce_share(const KEY& key)
    {
        return SPTR<Base>(produce(key));
    }

    static UPTR<Base> produce_unique(const KEY& key)
    {
        return UPTR<Base>(produce(key));
    }

protected:

    static Factory<Base>& Get()
    {
        static Factory<Base> factory;
        return factory;
    }

    static MAP_KEY_GENERATOR<Base> _mapFunc;
};

template<typename Base>
Factory<Base>::MAP_KEY_GENERATOR<Base> Factory<Base>::_mapFunc;


