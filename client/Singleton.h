#ifndef SINGLETON_H
#define SINGLETON_H

#include <assert.h>

/**
 * @class Singleton
 * @brief Singleton design pattern implementation
 * @tparam T The type of the singleton object
 */
template <class T>
class Singleton
{
public:
    /**
     * @brief Get the instance of the singleton object
     * @return Pointer to the singleton object
     */
    static T* Instance()
    {
        if (!m_Instance) m_Instance = new T;
        assert(m_Instance != nullptr);
        return m_Instance;
    }

protected:
    /**
     * @brief Protected constructor to prevent direct instantiation
     */
    Singleton();
        /**
     * @brief Protected destructor to prevent direct deletion
     */
    ~Singleton();

private:
    /**
     * @brief Private copy constructor to prevent copying
     * @param other Const reference to the object to be copied
     */
    Singleton(Singleton const&);
    /**
     * @brief Private assignment operator to prevent assignment
     * @param other Const reference to the object to be assigned
     * @return Reference to the current object
     */
    Singleton& operator=(Singleton const&);
    /**
     * @brief Pointer to the singleton instance
     */
    static T* m_Instance;
};

template <class T> T* Singleton<T>::m_Instance = nullptr;

#endif // SINGLETON_H
