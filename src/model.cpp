// #ifndef MODEL_H_
// #define MODEL_H_

#include <string>
#include "obj_data.h"
#include <list>

namespace s21 {

class Subject;

class Observer {
public:
    virtual ~Observer() {};
    virtual void SetSubject(Subject* subject) {_subject = subject;};
    virtual void RemoveSubject() {_subject = nullptr;};
    virtual Subject* GetSubject() {return _subject;};
    virtual void Update() = 0;
// protected:
//     Observer();
private:
    Subject* _subject;
};

class Subject {
public:
    virtual ~Subject() {};
    virtual void Attach(Observer* add_o) {
        _observers.push_back(add_o);
        add_o->SetSubject(this);   
    };
    virtual void Detach(Observer* rem_o) {
        _observers.remove(rem_o);
        rem_o->RemoveSubject();   
    };
    virtual void Notify() {
        for(std::list<Observer*>::iterator st = _observers.begin(), end = _observers.end(); st != end; ++st) {
            (*st)->Update();
        }
    };
// protected:
//     Subject();
private:
    std::list<Observer*> _observers;
};

class PositionModelSettings : public Subject {
public:
    PositionModelSettings() : _x_val(0), _y_val(0), _z_val(0), _x_angle(0), _y_angle(0), _z_angle(0), _scale(1) {};

    double GetAngleX() {return _x_angle;};
    double GetAngleY() {return _y_angle;};
    double GetAngleZ() {return _z_angle;};

    double GetPosX() {return _x_val;};
    double GetPosY() {return _y_val;};
    double GetPosZ() {return _z_val;};

    double GetScale() {return _scale;};
    
    void SetAngleX(double x) {
        _x_angle = x;
        Notify();
    };

    void SetAngleY(double y) {
        _y_angle = y;
        Notify();
    };

    void SetAngleZ(double z) {
        _z_angle = z;
        Notify();
    };

    void SetPosX(double x) {
        _x_val = x;
        Notify();
    };

    void SetPosY(double y) {
        _y_val = y;
        Notify();
    };

    void SetPosZ(double z) {
        _z_val = z;
        Notify();
    };

    void SetScale(double zoom) {
        _scale = zoom;
        Notify();
    };
private:
    double _x_val;
    double _y_val;
    double _z_val;

    double _x_angle;
    double _y_angle;
    double _z_angle;

    double _scale;
};

class Model : public Observer {
public:
    Model() {}; // нужно понять есть ли у структур дефолтный конструктор
    Model(s21::DataObj data, s21::Transform transform) : _data(data), _transform(transform) {};

    // DrawModel();

    void ChangeMoveVals(PositionModelSettings* settings) {
        _transform.prev_angle_x = settings->GetAngleX();
        _transform.prev_angle_y = settings->GetAngleY();
        _transform.prev_angle_z = settings->GetAngleZ();

        _transform.prev_coor[0] = settings->GetPosX();
        _transform.prev_coor[1] = settings->GetPosY();
        _transform.prev_coor[2] = settings->GetPosZ();

        _transform.value = settings->GetScale();
    }

    void Update() override {
        ChangeMoveVals(dynamic_cast<PositionModelSettings*>(GetSubject())); 
    };

    s21::DataObj* GetDataP() {return &_data;};

private:
    s21::DataObj _data;
    s21::Transform _transform;
};

// class GlobalViewSettings { //need to complite
// public:
//    static GlobalViewSettings* Instance() {
//         if (_instance == 0) {
//             _instance = new GlobalViewSettings;
//         }
//         return _instance;
//    };

//     void SetProectionType(bool type);
//     void SetBackColor(int color);

// protected:
//     GlobalViewSettings();
    
// private:
//     static GlobalViewSettings* _instance = 0;
//     static bool _type_of_proection;
//     static int _higth_color;
//     static double _higth_size;
//     static double _higth_style;
//     static int _ribs_color;
//     static double _ribs_size;
//     static double _ribs_style;
//     static int _back_colour;
// };

}

// #endif
