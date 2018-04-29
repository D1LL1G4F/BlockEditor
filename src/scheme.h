/*! \file      scheme.h
 *  \brief     header file for Scheme class
 *  \author    Matej Knazik
 *  \date      2018
 */

#ifndef SCHEME_H
#define SCHEME_H

#include <vector>
#include "block.h"
#include <boost/property_tree/ptree.hpp>

namespace json = boost::property_tree;

//!  Scheme class
/*!
  A backend class representing single scheme.
*/
class Scheme
{


public:
    //! Constructor
    /*!
        constucts Scheme
    */
    Scheme();

    //! Destructor
    /*!
        destructs Scheme
    */
    ~Scheme();

    //! Method indicating whenever scheme contains loops
    /*!
        \return bool indicating loop
    */
    bool isSchemeLooped();

    //! Perfrorms one step of simulation
    /*!
        \exception throws string if scheme is empty or isn't complete
        \return vector of integers that represent indexes of calculated blocks
    */
    std::vector<int> simulateStep();

    //! Method for reseting simulation to default state
    /*!
        \return void
    */
    void resetSimulation();

    //! Returns last index of block in scheme
    /*!
        \return int number of index
    */
    int getLastBlockIndex();

    //! Says if simulation is finished
    /*!
        \return bool
    */
    bool isSimulationFinished();

    //! Method to get pointer to block on certain index
    /*!
        \param int index of wanted block
        \return pointer to Block
    */
    Block* getBlock(int index);

    //! Performs serialization of scheme to JSON format
    /*!
        \return boost::property_tree root of created JSON tree
    */
    json::ptree serializeToJson();

    //! Performs serialization of scheme to JSON format
    /*!
        \return boost::property_tree root of created JSON tree
    */
    void loadScheme(json::ptree root);

    //! Adds block to scheme
    /*!
        \param pointer to block that has to be added
        \return pointer to added block
    */
    Block* addBlock(Block *block);

    //! Removes block from scheme
    /*!
        \param index of block to remove
        \return void
    */
    void removeBLock(int idx);

    //! Removes connection of port on specified coords
    /*!
        \param double x coordinate
        \param double y coordinate
        \return void
    */
    void removeLinkOnPort(double x, double y);

    //! Clears whole scheme
    /*!
        \return void
    */
    void clear();

private:

    //! recursive function for detecting loops
    bool isLooped(Block *block, int maxDepth, int currentDepth);

    //! return all block that should be calculated
    std::vector<Block *> getReadyBlocks();

    //! indicating whenever scheme has all ports set
    bool isSchemeComplete();

    //! looks up index of block by its pointer
    int getIdxByBlock(Block *blockPtr);

    //! looks up Port b its coordinates
    Port *getPortByCoords(double x, double y);

    //! indexes of already calculated blocks
    std::vector<int> alreadyCalculated;

    //! vector of all blocks in scheme
    std::vector<Block*> blocks;
};

#endif // SCHEME_H
