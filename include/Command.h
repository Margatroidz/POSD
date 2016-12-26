#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
#include <stack>

class Command
{
public:
    virtual void Excute() = 0;
    virtual void Unexcute() = 0;
protected:
    Command();
};

class CommandManager
{
public:
    CommandManager();
    void Excute(Command* command);
    void Undo();
    void Redo();
private:
    std::stack<Command *> undo;
    std::stack<Command *> redo;
};

class DefineCommand : public Command
{
public:
    void Excute();
    void Unexcute();
};

class AddCommand : public Command
{
public:
    void Excute();
    void Unexcute();
};

class DeleteCommand : public Command
{
public:
    void Excute();
    void Unexcute();
};

#endif // COMMAND_H_INCLUDED
