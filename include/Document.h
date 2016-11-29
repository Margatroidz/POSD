#ifndef DOCUMENT_H
#define DOCUMENT_H
#include <fstream>

class Document
{
public :
    virtual ~Document() {};
    std::string openDocument(const std::string name)
    {
        if(!canOpenDocument(name))
            throw std::string("file is not existed.");
        openFile(name);
        return readFile();
    }
protected :
    virtual void openFile(const std::string name) = 0;
    virtual bool canOpenDocument(const std::string name) = 0;
    virtual std::string readFile() = 0;
};

class MyDocument : public Document
{
private:
    virtual void openFile(const std::string name);
    virtual bool canOpenDocument(const std::string name);
    virtual std::string readFile();
    std::fstream _fstream;
};

#endif // DOCUMENT_H
