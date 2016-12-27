#include "Command.h"

CommandManager :: CommandManager()
{

}

void CommandManager :: Excute(Command* command)
{
    command->Excute(true);
    undo.push(command);
    while (!redo.empty())
    {
        Command* top = redo.top();
        delete top;
        redo.pop();
    }
}

void CommandManager :: Undo()
{
    if(!undo.empty()){
        Command* top = undo.top();
        top->Unexcute();
        undo.pop();
        redo.push(top);
    } else throw "there is no command to undo !";
}

void CommandManager :: Redo()
{
    if(!redo.empty()){
        Command* top = redo.top();
        top->Excute(false);
        redo.pop();
        undo.push(top);
    } else throw "there is no command to redo !";
}
