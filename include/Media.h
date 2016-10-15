#ifndef MEDIA_H
#define MEDIA_H
#include "Shapes.h"
#include "vector"

using namespace std;

class MediaVisitor;
class AreaVisitor;
class Media
{
public:
    Media();
    virtual ~Media();
    virtual void Accept(MediaVisitor* vistor);
};

class ComboMedia : public Media
{
public:
    ComboMedia(Media* media1, Media* media2);
    void Add(Media* media);
    void Accept(MediaVisitor* vistor);
private:
    vector<Media*> _medias;
};

class ShapeMedia : public Media
{
public:
    ShapeMedia(Shape* shape);
    virtual ~ShapeMedia();
    void Accept(MediaVisitor* vistor);
    virtual double Area();
    virtual double Perimeter();
private:
    Shape* _shape;
};

class MediaVisitor
{
public:
    MediaVisitor();
    virtual ~MediaVisitor();
    virtual void Visit(ShapeMedia* shapeMedia);
    virtual void Visit(ComboMedia* comboMedia);
};

class AreaVisitor : public MediaVisitor
{
public:
    AreaVisitor();
    virtual ~AreaVisitor();
    void Visit(ShapeMedia* shapeMedia);
    void Visit(ComboMedia* comboMedia);
    double TotalArea() const;
private:
    double _total;
};

class PerimeterVisitor : public MediaVisitor
{
public:
    PerimeterVisitor();
    virtual ~PerimeterVisitor();
    void Visit(ShapeMedia* shapeMedia);
    void Visit(ComboMedia* comboMedia);
    double TotalPerimeter() const;
private:
    double _total;
};

#endif // MEDIA_H
