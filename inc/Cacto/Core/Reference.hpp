#pragma once

namespace cacto
{

    template <typename T>
    class Reference
    {

    public:
        T *getInstance() const;
        bool isOwning() const;

        Reference(T &borrowing);
        Reference(T &&moving);
        Reference(T *intance, bool owned = false);

        template <typename U>
        Reference(U &borrowing);

        template <typename U>
        Reference(U &&moving);

        template <typename U>
        Reference(U *instance, bool owned = false);

        Reference(std::nullptr_t = 0);
        virtual ~Reference();

        Reference(const Reference<T> &other) = delete;
        Reference<T> &operator=(const Reference<T> &other) = delete;

        Reference(Reference<T> &&other);
        Reference<T> &operator=(Reference<T> &&other);

        bool operator==(const Reference<T> &other) const;
        bool operator!=(const Reference<T> &other) const;

        T &operator*() const;
        T *operator->() const;

    private:
        void drop();

        T *m_instance;
        bool m_isOwning;
    };

}

#include <Cacto/Core/Reference.inl>