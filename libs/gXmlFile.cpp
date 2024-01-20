/*!
 * =============================================================================
 *
 *   @file: gXmlFile.cpp
 *
 *   @date: December, 2023
 *
 * @author: Gino Francesco Bogo
 *
 * =============================================================================
 */

#include "gXmlFile.hpp"

#include "gXmlNode.hpp"
#include "gXmlPair.hpp"

#include <qfileinfo.h>
#include <qforeach.h>
#include <qiodevice.h>
#include <qxmlstream.h>

gXmlFile::gXmlFile() {
    m_root.name = "root";

    m_root.attributes.append(gXmlPair("author", "Gino Francesco Bogo"));
}

bool gXmlFile::open(const QString& filepath) {
    const auto& fileinfo = QFileInfo(filepath);

    if (fileinfo.exists() && fileinfo.isFile()) {
        QFile file(filepath);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            m_reader.setDevice(&file);

            xmlToNode(&m_root);
            file.close();

            return true;
        }
    }

    return false;
}

bool gXmlFile::save(const QString& filepath) {
    const auto& fileinfo = QFileInfo(filepath);

    if (fileinfo.isDir()) {
        return false;
    }

    QFile file(filepath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        m_writer.setDevice(&file);
        m_writer.setAutoFormatting(true);

        m_writer.writeStartDocument();
        m_writer.writeComment(QString(" PLEASE, DO NOT EDIT THIS FILE! "));

        nodeToXml(&m_root);
        file.close();
    }

    return true;
}

void find_node(gXmlNode* start, gXmlNode** child, const QString& name) {
    if ((start == nullptr) || (*child != nullptr)) {
        return;
    }

    if (start->name == name) {
        *child = start;
    }
    else {
        foreach (auto* item, start->children) {
            find_node(item, child, name);
        }
    }
}

gXmlNode* gXmlFile::findNode(gXmlNode* start, const QString& name) {
    if (start == nullptr) {
        start = &m_root;
    }

    gXmlNode* child = nullptr;

    find_node(start, &child, name);

    return child;
}

gXmlNodes gXmlFile::findNodes(gXmlNode* start, const QString& name) {
    gXmlNodes nodes;

    if (start == nullptr) {
        start = &m_root;
    }

    gXmlNode* first = findNode(start, name);

    if (first != nullptr) {
        start = first->parent;

        foreach (auto* child, start->children) {
            if (child->name == name) {
                nodes.append(child);
            }
        }
    }

    return nodes;
}

gXmlNode* gXmlFile::insertNode(gXmlNode* parent, const QString& name) {
    auto* node = new gXmlNode();

    if (parent == nullptr) {
        parent = &m_root;
    }

    node->parent = parent;
    node->name   = name;

    parent->children.append(node);

    return node;
}

QString gXmlFile::getAttribute(gXmlNode* node, const QString& name) {
    if (node != nullptr) {
        foreach (auto pair, node->attributes) {
            if (pair.name() == name) {
                return pair.value();
            }
        }
    }

    return {""};
}

bool gXmlFile::setAttribute(gXmlNode* node, const gXmlPair& pair) {
    if (node != nullptr) {

        for (int i = 0; i < node->attributes.count(); ++i) {
            gXmlPair& item = node->attributes[i];
            if (item.name() == pair.first) {
                item.value(pair.second);
                return true;
            }
        }

        node->attributes.append(pair);
        return true;
    }

    return false;
}

void gXmlFile::xmlToNode(gXmlNode* node) {
    if (node == nullptr) {
        return;
    }

    static bool first_loop = true;

    m_reader.readNext();

    if (!m_reader.atEnd()) {
        const auto token = m_reader.tokenType();

        switch (token) {
            case QXmlStreamReader::StartDocument: {
                m_root.clear();
            } break;

            case QXmlStreamReader::StartElement: {
                if (first_loop) {
                    first_loop = false;
                }
                else {
                    node = new gXmlNode(node);
                }

                node->name = m_reader.name().toString();

                foreach (const auto& attribute, m_reader.attributes()) {
                    const auto& name  = attribute.name().toString();
                    const auto& value = attribute.value().toString();

                    node->attributes.append(gXmlPair(name, value));
                }
            } break;

            case QXmlStreamReader::Characters: {
                node->text = m_reader.text().toString().trimmed();
            } break;

            case QXmlStreamReader::EndElement: {
                node = node->parent;
            } break;

            case QXmlStreamReader::EndDocument: {
                first_loop = true;
            } break;

            default: {
            } break;
        }

        xmlToNode(node);
    }
}

void gXmlFile::nodeToXml(gXmlNode* node) {
    if (node == nullptr) {
        return;
    }

    m_writer.writeStartElement(node->name);

    foreach (gXmlPair pair, node->attributes) {
        m_writer.writeAttribute(pair.name(), pair.value());
    }

    if (!node->text.isEmpty()) {
        m_writer.writeCharacters(node->text);
    }

    foreach (gXmlNode* child, node->children) {
        nodeToXml(child);
    }

    m_writer.writeEndElement();
}

/* =============================================================================
   End of file
 */
