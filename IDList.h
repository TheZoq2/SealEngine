#ifndef H_ID_LIST
#define H_ID_LIST

#include <vector>
#include <set>
#include <iostream>

namespace zen
{
    template<class T>
    class IDList
    {
    public:
        /*
         *  Add an element to the list and return the ID of that value
         *
         *  O(1) plus possible removal of available ID
         */
        std::size_t push_back(T* value)
        {
            std::cout << freeSlots.size() << "   " << data.size() << "   " << cachedElements.size() << std::endl;
            hasCachedElements = false;
            if(freeSlots.size() > 0)
            {
                std::size_t id = *(freeSlots.begin());

                data[id] = value;
                freeSlots.erase(freeSlots.begin());
                return id;
            }

            data.push_back(value);

            return data.size() - 1;
        }


        /*
         *  Return the element at the specified ID. nullptr if there is no such element
         *
         *  O(1)
         */
        T* at(std::size_t id) const
        {
            if(data.size() >= id)
            {
                return nullptr;
            }

            return data.at(id);
        }

        /*
         *  Set the pointer with the specified ID to nullptr. Add the ID to the set of available
         *  IDs if it wasn't already in the list. Note that no delete operation is run which means that memory
         *  needs to be manually freed
         *
         *  O(1)
         */
        void forget(std::size_t id)
        {
            if(data.size() > id)
            {
                hasCachedElements = false;

                freeSlots.insert(id);

                data[id] = nullptr;
            }
        }

        /*
         *  Return the amount of elements currently in the list 
         *
         *  O(1)
         */
        std::size_t size() const
        {
            return data.size() - freeSlots.size();
        }


        /*
         *  Get a new vector containing all elements in the vector that are not null.
         *
         *  O(n)
         */
        std::vector<T*> getElements()
        {
            if(hasCachedElements)
            {
                return cachedElements;
            }

            hasCachedElements = true;
            for(T* elements : data)
            {
                cachedElements.push_back(elements);
            }

            return cachedElements;
        }
    private:
        std::vector<T*> data = std::vector<T*>();
        std::set<std::size_t> freeSlots = std::set<std::size_t>();

        bool hasCachedElements = false;
        std::vector<T*> cachedElements;
    };
} /* zen */ 
#endif
