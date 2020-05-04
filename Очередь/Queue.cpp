#include "Queue.h"
#include "ListQueue.h"
#include "List2Queue.h"
#include "VectorQueue.h"
#include "QueueImplementation.h"

#include <stdexcept>

using namespace std;

Queue::Queue(QueueContainer container)
	: _containerType(container)
{
	switch (container)
	{
	case QueueContainer::List :{
		_pimpl = new ListQueue();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case QueueContainer::List2	:{
		_pimpl = new ListQueue();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	case QueueContainer::Vector :{
		_pimpl = new VectorQueue();	// конкретизируйте под ваши конструкторы, если надо
		break;
	}
	default:
		throw std::runtime_error("Неизвестный тип контейнера");
	}
}

Queue::Queue(const ValueType* valueArray, const size_t arraySize, QueueContainer container)

    : _containerType(container)
    {
    switch (container)
    {
		case QueueContainer::List: {
        _pimpl = new ListQueue();// конкретизируйте под ваши конструкторы, если надо
        for(size_t i = 0; i < arraySize;i++)
		{
            _pimpl->pushQueue(valueArray[i]);
        }
        break;
        }
		case QueueContainer::List2: {
		_pimpl = new List2Queue();// конкретизируйте под ваши конструкторы, если надо
		for (size_t i = 0; i < arraySize; i++)
		{
		_pimpl->pushQueue(valueArray[i]);
		}
		break;
		}
       case QueueContainer::Vector: {
       _pimpl = new VectorQueue(); // конкретизируйте под ваши конструкторы, если надо
       for(size_t i = 0; i < arraySize;i++)
       {
           _pimpl->pushQueue(valueArray[i]);
       }
       break;
       }
       default:
           throw std::runtime_error("Неизвестный тип контейнера");
       }
    }

Queue::Queue(const Queue& copyQueue)
 : _containerType(copyQueue._containerType), _pimpl(copyQueue._pimpl)
{
	*_pimpl = *(copyQueue._pimpl);
}

Queue& Queue::operator=(const Queue& copyQueue) {
    int copySize = copyQueue.size();
    if(copyQueue._containerType == QueueContainer::List) {
        _pimpl = new ListQueue();// конкретизируйте под ваши конструкторы, если надо
    }
	if (copyQueue._containerType == QueueContainer::List2) {
		_pimpl = new List2Queue();// конкретизируйте под ваши конструкторы, если надо
	}
    if(copyQueue._containerType == QueueContainer::Vector) {
        _pimpl = new VectorQueue();    // конкретизируйте под ваши конструкторы, если надо
    }
    ValueType* array = new ValueType[copySize];
    for (int i = copySize - 1; i >= 0; i--) {
        array[i] = copyQueue._pimpl->top();
        copyQueue._pimpl->popQueue();
    }
    for (int i = 0; i < copySize; i++) {
        _pimpl->pushQueue(array[i]);
        copyQueue._pimpl->pushQueue(array[i]);
    }
    delete[] array;
    return *this;
    // TODO: вставьте здесь оператор return
}

Queue::~Queue()
{
	delete _pimpl;		// композиция!
}

void Queue::push(const ValueType& value)
{
	// можно, т.к. pushStack определен в интерфейсе
    _pimpl->pushQueue(value);
}

void Queue::pop()
{
    _pimpl->popQueue();
}

const ValueType& Queue::top() const
{
	return _pimpl->top();
}

bool Queue::isEmpty() const
{
	return _pimpl->isEmptyQueue();
}

size_t Queue::size() const
{
	return _pimpl->sizeQueue();
}