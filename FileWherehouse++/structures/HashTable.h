/**
 * @file HashTable.h
 * @date 4/3/16
 * @title Tabla Hash
 * @brief Abstracion de una tabla hash para el proyecto xC++2
 */

#ifndef HashTable_h
#define HashTable_h

#include "LinkedList.h"

template<class AnyType>
class HashTable
{
private:

    LinkedList<AnyType> * array;

    int length;

    int hash( string itemKey );

public:

    /**
     * @brief M\'etodo constructor de HashTable
     * @param int pTableLength 13 por default
     */
    HashTable( int pTableLength = 13 );

    /**
     * @brief M\'etodo inserta el nodo
     * @param NodoSimple<AnyType>* pNewItem
     */
    void insertItem( NodoSimple<AnyType> * pNewItem );

    /**
     * @brief Metodo inserta el item
     * @param AnyType pItem
     */
    void insertItem(AnyType* pItem);

    /**
     * @brief Metodo elimina el item segun el pItemKey
     * @param string pItemKey
     * @return bool
     */
    bool removeItem( string pItemKey );

    // Returns an item from the Hash Table by key.
    // If the item isn't found, a null pointer is returned.
    /**
     * @brief Metodo busca el elemento segun el pItemKey
     * @param string pItemKey
     * @return nodoSimple<AnyType>*
     */
    NodoSimple<AnyType> * getItemByKey( string pItemKey );

    /**
     * @brief Metodo devuelve el dato segun pItemKey
     * @param string pItemKey
     * @return AnyType*
     */
    AnyType* getDataByKey(string pItemKey);

    /**
     * @brief Metodo devuelve el nado numero pNumElem
     * @param int pNumElem
     * @return NodoSimple<AnyType>*
     */
    NodoSimple<AnyType>* getItemByNumElem(int pNumElem);

    /**
     * @brief Metodo imprime la tabla
     */
    void printTable();

    /**
     * @brief imprime el histograma con la informacion
     */
    void printHistogram();

    /**
     * @brief Metodo devuelve el atributo /_Length
     * @return int
     */
    int getLength();

    /**
     * @brief Metodo develve la cantidad de elementos
     * @return int
     */
    int getNumberOfItems();

    /**
     * @brief Metodo destructor de HashTable
     */
    ~HashTable();
};

template<class AnyType>
HashTable<AnyType>::HashTable( int tableLength )
{
    if (tableLength <= 0) tableLength = 13;
    array = new LinkedList<AnyType>[ tableLength ];
    length = tableLength;
}

template<class AnyType>
int HashTable<AnyType>::hash( string itemKey )
{
    int value = 0;
    for ( int i = 0; i < itemKey.length(); i++ )
        value += itemKey[i];
    return (value * itemKey.length() ) % length;
}

template<class AnyType>
void HashTable<AnyType>::insertItem( NodoSimple<AnyType> * newItem )
{
    int index = hash( newItem->getKey());
    array[ index ].insertItem( newItem );
}

template<class AnyType>
bool HashTable<AnyType>::removeItem( string itemKey )
{
    int index = hash( itemKey );
    return array[ index ].removeItem( itemKey );
}

template<class AnyType>
NodoSimple<AnyType> * HashTable<AnyType>::getItemByKey( string itemKey )
{
    int index = hash( itemKey );
    return array[ index ].getItem( itemKey );
}

template<class AnyType>
AnyType* HashTable<AnyType>::getDataByKey(string pItemKey){
	NodoSimple<AnyType> *nodo = getItemByKey(pItemKey);
	return nodo->val;
}

template<class AnyType>
NodoSimple<AnyType>* HashTable<AnyType>::getItemByNumElem(int pNumElem){
	int elem = 0;
	int index = 0;
	while(elem < pNumElem){
		elem = elem +array[index].getLength();
		index++;
	}
	index--;
	elem = pNumElem - (elem - array[index].getLength());
	return array[index].getItemByPosition(elem);
}

template<class AnyType>
void HashTable<AnyType>::printTable()
{
    cout << "\n\nHash Table:\n";
    for ( int i = 0; i < length; i++ )
    {
        cout << "Bucket " << i + 1 << ": ";
        array[i].printList();
    }
}

template<class AnyType>
void HashTable<AnyType>::printHistogram()
{
    cout << "\n\nHash Table Contains ";
    cout << getNumberOfItems() << " Items total\n";
    for ( int i = 0; i < length; i++ )
    {
        cout << i + 1 << ":\t";
        for ( int j = 0; j < array[i].getLength(); j++ )
            cout << " X";
        cout << "\n";
    }
}

template<class AnyType>
int HashTable<AnyType>::getLength()
{
    return length;
}

template<class AnyType>
int HashTable<AnyType>::getNumberOfItems()
{
    int itemCount = 0;
    for ( int i = 0; i < length; i++ )
    {
        itemCount += array[i].getLength();
    }
    return itemCount;
}

template<class AnyType>
HashTable<AnyType>::~HashTable()
{
    delete [] array;
}

#endif
