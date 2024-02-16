#ifndef GLWIDGET_H
#define GLWIDGET_H

// #include <GL/glu.h>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
//#include <GL/gl.h>
#include <GL/glu.h>
#endif

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
#include "../Model/model.cpp"
#include "../Model/parser.h"

class GLWidget : public QOpenGLWidget {
  Q_OBJECT

 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  QString modelPath;

  s21::PositionModelSettings* pos_settings = new s21::PositionModelSettings;
  s21::Model* model =  new s21::Model;
  s21::GlobalViewSettings& global_settings = s21::GlobalViewSettings::Instance();
  void initialize_model();

protected:
  void initializeGL(); 
  void paintGL();
  void resizeGL(int w, int h);

 public slots:
  void change_vertices_color();
  void change_edges_color();
  void change_background_color();
  void set_edges_type(int type);
  void set_line_width(int size);
  void set_vertices_method(int type);
  void set_vertices_size(int size);
  void set_projection_type(int type);
  void on_rotation_x_spinbox_valueChanged(double arg1);
  void on_rotation_y_spinbox_valueChanged(double arg1);
  void on_rotation_z_spinbox_valueChanged(double arg1);
  
  void on_position_x_spinbox_valueChanged(double arg1);
  void on_position_y_spinbox_valueChanged(double arg1);
  void on_position_z_spinbox_valueChanged(double arg1);
  void on_model_scale_slider_valueChanged(int arg1);
};
#endif  // GLWIDGET_H
