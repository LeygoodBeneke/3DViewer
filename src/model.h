#ifndef MODEL_H_
#define MODEL_H_

#include <string>

class Model {
public:
    using matrix_t = int;
    using poligon_t = char;
    
    Model(matrix_t coords, poligon_t* poligons);
    
    void DrawModel();
    
private:
    matrix_t coordinates_;
    poligon_t* poligons_;
    CoordinateView* cords_pos;
};

class CoordinateView {
public:
    CoordinateView();

    void MoveX();
    void MoveY();
    void MoveZ();
    void TurnX();
    void TurnY();
    void TurnZ();
    void SetScale();

    int GetXAngle();
    int GetYAngle();
    int GetZAngle();
    int GetXMove();
    int GetYMove();
    int GetZMove();
    int GetScale();
private:
    int x_angle_;
    int y_angle_;
    int z_angle_;
    int x_move_;
    int y_move_;
    int z_move_;
    int scale_;

};

class GlobalViewSettings {
public:
    GlobalViewSettings* Instance();

    void SetProectionType(bool type);
    void SetBackColor(int color);
    void GetHigth();
    void GetRibs();

protected:
    GlobalViewSettings();
    
private:
    static GlobalViewSettings* _instance;
    static bool _type_of_proection;
    static Higth _higth;
    static Ribs _ribs;
    static int _back_colour;
};

class Higth {
public:
    Higth(ShowHigthStrategy cur_higth_style);

    void SetHigthStyle(ShowHigthStrategy cur_style);
    void SetColor();
    void SetSize();

    void CreateHigth();
private:
    int _color;
    double _size;
    ShowHigthStrategy _current_higth_style;
};

class ShowHigthStrategy {
public:
    virtual void Style();
};

class HideHigth : ShowHigthStrategy {
public:    
    void Style() override;
};

class CircleHigth : ShowHigthStrategy {
public:    
    void Style() override;
};

class SquareHigth : ShowHigthStrategy {
public:    
    void Style() override;
};

class Ribs {
public:
    Ribs(ShowRibsStrategy cur_rib_style);
    
    void SetRibsStyle(ShowRibsStrategy cur_style );
    void SetColor();
    void SetThick();
    void CreateRibs();

private:
    int color_;
    double thick_;
    ShowRibsStrategy current_ribs_show_;
};

class ShowRibsStrategy  {
public:
    virtual void Style();
};

class SolidRibs : ShowRibsStrategy {
public:    
    void Style() override;
};

class DotRibs : ShowRibsStrategy {
public:
    void Style() override;
};



#endif
