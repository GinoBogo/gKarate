/*!
 * =============================================================================
 *
 *   @file: gXmlFile.hpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#ifndef GXMLFILE_HPP
#define GXMLFILE_HPP

#include "gXmlNode.hpp"

#include <QList>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class gXmlFile {
  public:
    gXmlFile();

    bool open(const QString& filepath);
    bool save(const QString& filepath);

    [[nodiscard]] gXmlNode* getRoot() {
        return &m_root;
    }

    [[nodiscard]] const QString& getRootName() const {
        return m_root.name;
    }
    void setRootName(const QString& name) {
        m_root.name = name;
    }

    gXmlNode* findNode(gXmlNode* start, const QString& name);
    gXmlNodes findNodes(gXmlNode* start, const QString& name);
    gXmlNode* insertNode(gXmlNode* parent, const QString& name);

    static QString getAttribute(gXmlNode* node, const QString& name);
    static bool    setAttribute(gXmlNode* node, const gXmlPair& pair);

  private:
    void xmlToNode(gXmlNode* node);
    void nodeToXml(gXmlNode* node);

  private:
    QXmlStreamReader m_reader;
    QXmlStreamWriter m_writer;

    gXmlNode m_root;
};

#endif // GXMLFILE_HPP
