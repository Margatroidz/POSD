#ifndef MEDIA_H
#define MEDIA_H
#include "Shapes.h"
#include <vector>
#include <sstream>

using namespace std;

class AreaVisitor;
class PerimeterVisitor;
class DescriptionVisitor;
class Media
{
public:
    Media();
    virtual ~Media();
    virtual void Accept(AreaVisitor* visitor) = 0;
    virtual void Accept(PerimeterVisitor* visitor) = 0;
    virtual void Accept(DescriptionVisitor* visitor) = 0;
    virtual void RemoveMedia(Media* media) = 0;
};

class ComboMedia : public Media
{
public:
    ComboMedia();
    ComboMedia(Media* media1, Media* media2);
    void Accept(AreaVisitor* visitor);
    void Accept(PerimeterVisitor* visitor);
    void Accept(DescriptionVisitor* visitor);
    void RemoveMedia(Media* media);
    void Add(Media* media);
private:
    vector<Media*> _medias;
};

class ShapeMedia : public Media
{
public:
    ShapeMedia(Shape* shape);
    ~ShapeMedia();
    void Accept(AreaVisitor* visitor);
    void Accept(PerimeterVisitor* visitor);
    void Accept(DescriptionVisitor* visitor);
    void RemoveMedia(Media* media);
    double Area();
    double Perimeter();
    string Description();
private:
    Shape* _shape;
};

class TextMedia : public Media
{
public:
    TextMedia(Rectangle* rectangle, string text);
    ~TextMedia();
    void Accept(AreaVisitor* visitor);
    void Accept(PerimeterVisitor* visitor);
    void Accept(DescriptionVisitor* visitor);
    void RemoveMedia(Media* media);
    string Text();
private:
    Rectangle* _rectangle;
    string _text;
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

class DescriptionVisitor : public MediaVisitor
{
public:
    DescriptionVisitor();
    virtual ~DescriptionVisitor();
    void Visit(ShapeMedia* shapeMedia);
    void Visit(ComboMedia* comboMedia);
    void AddCombo(int amount);
    void CompleteCombo();
    string Description() const;
private:
    vector<int> _remainCombo;
    stringstream _descriptionStream;
    void CompleteCombo(int size);
};

class MediaBuilder
{
public:
    virtual ~MediaBuilder() {};
    virtual void BuildComboMedia() = 0;
    virtual void BuildShapeMedia(Shape * s) = 0;
    virtual Media* GetMedia() = 0;
};

class ShapeMediaBuilder : public MediaBuilder
{
public:
    ShapeMediaBuilder();
    ~ShapeMediaBuilder();
    void BuildComboMedia();
    void BuildShapeMedia(Shape* s);
    Media* GetMedia();
private:
    ShapeMedia* _shape;
};

class ComboMediaBuilder : public MediaBuilder
{
public:
    ComboMediaBuilder();
    ~ComboMediaBuilder();
    void BuildComboMedia();
    void BuildShapeMedia(Shape* s);
    void BuildShapeMedia(Media* m);
    void RemoveMedia(Media* m);
    Media* GetMedia();
private:
    ComboMedia* _combo;
    vector<Media*> _shapesTemp;
};

#endif // MEDIA_H
