#include "toolbarmanager.h"

#include <QWidget>
#include <QToolBar>
#include <QIcon>

ToolbarManager::ToolbarManager(QObject *parent) : QObject(parent)
{

}

ToolbarManager::~ToolbarManager()
{
}

// Singleton
ToolbarManager& ToolbarManager::Instance()
{
    static ToolbarManager __instance;
    return __instance;
}

void ToolbarManager::AddAction(const QString & text, const QObject * receiver, const char * member)
{
    if(_toolbar)
    {
        _toolbar->addAction(text, receiver, member);
    }
}
void ToolbarManager::AddAction(const QString & text, const QObject * receiver, const char * member, QIcon icon)
{
    if(_toolbar)
    {
        _toolbar->addAction(icon, text, receiver, member);
    }
}

void ToolbarManager::Clear()
{
    _toolbar->clear();
}

