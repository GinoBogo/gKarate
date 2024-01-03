/*!
 * =============================================================================
 *
 *   @file: gXmlNode.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GXMLNODE_HPP
#define GXMLNODE_HPP

#include "gXmlPair.hpp"

#include <QList>
#include <QString>

class gXmlNode;

typedef QList<gXmlNode*> gXmlNodes;

class gXmlNode {
  public:
    gXmlNode(gXmlNode* parent = nullptr);
    ~gXmlNode();

    void clear();

    gXmlNode* parent;
    gXmlNodes children;

    QString   name;
    QString   text;
    gXmlPairs attributes;
};

#endif // GXMLNODE_HPP
