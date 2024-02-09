#pragma once

namespace cacto
{

    template <typename T>
    class Reference
    {

    public:
        bool isOwning() const;

        Reference(T &borrowing);
        Reference(T &&moving);

        Reference(T *intance = nullptr, bool owned = false);
        virtual ~Reference();

        Reference(const Reference<T> &other);
        Reference<T> &operator=(const Reference<T> &other);

        Reference(Reference<T> &&other);
        Reference<T> &operator=(Reference<T> &&other);

        operator bool() const;
        bool operator==(const Reference<T> &other) const;

        T &operator*() const;
        T *operator->() const;

    private:
        void drop();

        T *m_instance;
        bool m_isOwning;
    };

}

#include <Cacto/Core/Reference.inl>