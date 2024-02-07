#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glu.h>

#include <QColorDialog>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QImage>
#include <QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <QString>
#include <QVector>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include "../model.cpp"
#include "../parser.h"

class GLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  // using PositionModelSettings = s21::PositionModelSettings;
  // using Model = s21::Model;
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  // enum VerticesDisplayMethod { SQUARE, CIRCLE, BLANK };

  // enum EdgesType { SOLID, DASHED };

  // enum ProjectionType { PARALLEL, CENTRAL };

  QString modelPath;

  // QColor get_background() { return background; }
  // GLfloat get_width() { return line_width; }
  // EdgesType get_edges_type() { return edges_type; }
  // QColor get_edges_color() { return edges_color; }
  // VerticesDisplayMethod get_vetr_method() { return vetr_method; }
  // GLfloat get_vertices_size() { return vertices_size; }
  // QColor get_vertices_color() { return vertices_color; }
  // ProjectionType get_projection_type() { return projection_type; }

  // void set_background(QColor color) { background = color; }
  s21::PositionModelSettings* pos_settings = nullptr;
  s21::Model* model = nullptr;
  void initialize_model();

protected:
  void initializeGL(); 
  void paintGL();
  void resizeGL(int w, int h);
  // void rotation(double angle, double *, double *);
  // void set_vertices_color(QColor new_color);
  // void set_edges_color(QColor new_color);

  // int get_edges_count() { return line_array_len; }
  // int get_points_count() { return point_array_len; }

 private:
  // void drawStar(float fX, float fY);
  // void drawStars();
  // void drawStripes();
  // void drawAxis();

  // QColor background;
  // GLfloat line_width = 1.0;
  // GLfloat vertices_size = 5.0;

  // QColor vertices_color = Qt::white;
  // QColor edges_color = Qt::white;
  // EdgesType edges_type = EdgesType::SOLID;

  // double prev_angle_x = 0;
  // double prev_angle_y = 0;
  // double prev_angle_z = 0;

  // double position_x = 0;
  // double position_y = 0;
  // double position_z = 0;
  // double scale = 1.0;
  // double current_angle_x = 0;
  // double current_angle_y = 0;
  // double current_angle_z = 0;

 // point *point_array;
 // int point_array_len = 0;
 // line *line_array;
  // int line_array_len = 0;

  // VerticesDisplayMethod vetr_method = VerticesDisplayMethod::SQUARE;

  // ProjectionType projection_type = ProjectionType::PARALLEL;

 public slots:
  // void set_position_x(double);
  // void set_position_y(double);
  // void set_position_z(double);
  // void rotation_x(double angle);
  // void rotation_y(double angle);
  // void rotation_z(double angle);
  // void set_vertices_size(int);
  // void set_vertices_method(int);
  // void set_edges_type(int);
  // void set_line_width(int);
  // void set_scale(int size);
  // void set_projection_type(int);
  void on_rotation_x_spinbox_valueChanged(double arg1);
  void on_rotation_y_spinbox_valueChanged(double arg1);
  void on_rotation_z_spinbox_valueChanged(double arg1);
  
  void on_position_x_spinbox_valueChanged(double arg1);
  void on_position_y_spinbox_valueChanged(double arg1);
  void on_position_z_spinbox_valueChanged(double arg1);
  void on_model_scale_slider_valueChanged(int arg1);
};
#endif  // GLWIDGET_H
