#ifndef UNITTEST_H_INCLUDED
#define UNITTEST_H_INCLUDED
#include <iostream>
#include <cstring>
#include "Command.h"
#include "Media.h"

TEST(CommandManagerTest, CommandManager)
{
    CommandManager cm;
    std::map<string, MediaInfo*> m;
    Command* c1 = new DeleteCommand("def cSmall = Circle(2,1,1)", m);
    cm.Excute(c1);
    std::map<string, MediaInfo*>::iterator it = m.find("rTall");
    ASSERT(it != m.end());
    cm.Undo();
    ASSERT(it == m.end());
    cm.Redo();
    ASSERT(it != m.end());
}

TEST(DefineCommandTest, DefineCommand)
{
    CommandManager cm;
    std::map<string, MediaInfo*> m;

    Command* c = new DefineCommand("def rTall = Rectangle(1,10,2,8)", m);
    try
    {
        c.Excute(false);
        FAIL("error");
    }catch(const char* e)
    {
        ASSERT(strcmp(e, "variable cannot found !"));
    }
    m.Insert(std::pair(string("rTall"), new MediaInfo);
    c.Excute(false);
    std::map<string, MediaInfo*>::iterator it = m.find("rTall");
    ASSERT(it != m.end());
}

TEST(AddCommandTest, AddCommand)
{
    CommandManager cm;
    std::map<string, MediaInfo*> m;

    Command* c = new AddCommand("add rTall to comboExclamation", m);
    try
    {
        c.Excute(false);
        FAIL("error");
    }catch(const char* e)
    {
        ASSERT(strcmp(e, "variable cannot found !"));
    }
    MediaInfo* mif = new MediaInfo
    mif->media = new ComboMedia();
    mif->Combo = true;
    m.Insert(std::pair(string("comboExclamation"), mif);

    m.Insert(std::pair(string("rTall"), new MediaInfo);
    c.Excute(false);
    std::map<string, MediaInfo*>::iterator it = m.find("comboExclamation");
    ASSERT(strstr(it->second->def, "rTall") != NULL);
}

TEST(DeleteCommandTest, DeleteCommand)
{
    CommandManager cm;
    std::map<string, MediaInfo*> m;

    Command* c = new DeleteCommand("delete rTall", m);
    try
    {
        c.Excute(false);
        FAIL("error");
    }catch(const char* e)
    {
        ASSERT(strcmp(e, "variable cannot found !"));
    }
    m.Insert(std::pair(string("rTall"), new MediaInfo);
    c.Excute(false);
    std::map<string, MediaInfo*>::iterator it = m.find("rTall");
    ASSERT(it == m.end());
}

#endif // UNITTEST_H_INCLUDED
