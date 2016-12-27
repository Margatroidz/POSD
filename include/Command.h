#ifndef COMMAND_H_INCLUDED
#define COMMAND_H_INCLUDED
#include <string>
#include <map>
#include <stack>
#include <vector>

class Media;
class MediaInfo;
struct RetrieveData;
class Command
{
public:
    virtual ~Command(){};
    virtual void Excute(bool output) = 0;
    virtual void Unexcute() = 0;
protected:
    Command(){};
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
    DefineCommand(const char* input, std::map<std::string, MediaInfo*> &container);
    ~DefineCommand();
    void Excute(bool output);
    void Unexcute();
private:
    MediaInfo* temp;
    std::string tempName;
    bool isRetrieve;
    char* excuteCommand;
    std::map<std::string, MediaInfo*> &target;
    void Delete(char* input, std::map<std::string, MediaInfo*> &container);
    void ExtractShape(const char* input, int startPosition, std::map<std::string, MediaInfo*> &container);
    Media* CreateShape(char* input, std::map<std::string, MediaInfo*>& container, bool &isCombo, char* def);
    Media* CreateCombo(char* input, std::map<std::string, MediaInfo*>& container, char* def);
    std::string ReadString(const char* input, int& position);
    float ReadFloat(const char* input, int& position);
    void DefToSave(char* def);
    void DeleteDef(char* def, char* target);
};

class AddCommand : public Command
{
public:
    AddCommand(const char* input, std::map<std::string, MediaInfo*> &container);
    ~AddCommand();
    void Excute(bool output);
    void Unexcute();
private:
    char* excuteCommand;
    char* unexcuteCommand;
    std::map<std::string, MediaInfo*> &target;
    void Delete(char* input, std::map<std::string, MediaInfo*> &container);
    void Add(char* input, std::map<std::string, MediaInfo*> &container, bool output);
    void AddDef(char* def, char* target);
    void DeleteDef(char* def, char* target);
};

class DeleteCommand : public Command
{
public:
    DeleteCommand(const char* input, std::map<std::string, MediaInfo*> &container);
    ~DeleteCommand();
    void Excute(bool output);
    void Unexcute();
private:
    MediaInfo* temp;
    std::string tempName;
    bool isRetrieve;
    char* excuteCommand;
    char* unexcuteCommand;
    std::vector<RetrieveData*> retrieveData;
    std::map<std::string, MediaInfo*> &target;
    void Delete(char* input, std::map<std::string, MediaInfo*> &container);
    void Add(char* input, std::map<std::string, MediaInfo*> &container);
    void AddDef(char* def, char* target);
    RetrieveData* DeleteDef(char* def, char* target);
};

#endif // COMMAND_H_INCLUDED
