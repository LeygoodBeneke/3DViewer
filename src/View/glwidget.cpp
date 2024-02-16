#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
      //background(QColor(Qt::black)),
     // vertices_color(QColor(Qt::white))
    
{}

GLWidget::~GLWidget() {
  // if (point_array) free(point_array);
  // if (line_array) free(line_array);
}

void GLWidget::initializeGL() {
  glMatrixMode(GL_PROJECTION);
  glMatrixMode(GL_MODELVIEW);
  global_settings.SetHigthColor(QColor(Qt::white));
  global_settings.SetEdgeColor(QColor(Qt::white));
  global_settings.SetBackgroundColor(QColor(Qt::black));
  global_settings.SetEdgesType(0);
  global_settings.SetEdgesSize(1);
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, height, width);
}

void GLWidget::paintGL() {
  glClearColor(global_settings.GetBackgroundColor().redF(), global_settings.GetBackgroundColor().greenF(), global_settings.GetBackgroundColor().blueF(), 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (global_settings.GetProjectionType() == s21::GlobalViewSettings::ProjectionType::CENTRAL) {
    gluPerspective(70.0, 1.5, 0.1, 50);
  } else {
    glOrtho(-5, 5, -5, 5, -100, 100);
  }
  gluLookAt(2, 2, 4, 0, 0, 0, 0, 1, 0);

  s21::DataObj cur_data_obj = model->GetData();
  
  glEnable(GL_PROGRAM_POINT_SIZE);

  if (global_settings.GetVerticesDisplayMethod() == s21::GlobalViewSettings::VerticesDisplayMethod::CIRCLE) { // CIRCLE DONT WORK
    glEnable(GL_POINT_SMOOTH);
    glPointSize(global_settings.GetHigthSize());
  } else if (global_settings.GetVerticesDisplayMethod() == s21::GlobalViewSettings::VerticesDisplayMethod::BLANK) {
    glPointSize(1);
    glDisable(GL_POINT_SMOOTH);
  } else {
    glPointSize(global_settings.GetHigthSize());
    glDisable(GL_POINT_SMOOTH);
  }

  glBegin(GL_POINTS);
  glColor3f(global_settings.GetHigthColor().redF(), global_settings.GetHigthColor().greenF(), global_settings.GetHigthColor().blueF());
  for (unsigned int i = 0; i < cur_data_obj.vertexes.size(); i += 3) {
    glVertex3f(
        cur_data_obj.vertexes[i],
        cur_data_obj.vertexes[i + 1],
        cur_data_obj.vertexes[i + 2]
    );
  }
  glEnd();

  //GLfloat lineWidthRange[2] = {0.0f, 10.0f};
  //glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, lineWidthRange);
  if (global_settings.GetEdgesType() == s21::GlobalViewSettings::EdgesType::DASHED) {
    glEnable(GL_LINE_STIPPLE);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }
  glLineStipple(3, 0xDDDD);

  glLineWidth(global_settings.GetEdgesSize());

  glBegin(GL_LINES);
  glColor3f(global_settings.GetEdgeColor().redF(), global_settings.GetEdgeColor().greenF(), global_settings.GetEdgeColor().blueF());
  for (unsigned int i = 0; i < cur_data_obj.facets.size(); ++i) {
      glVertex3f(
        cur_data_obj.vertexes[cur_data_obj.facets[i] * 3],
        cur_data_obj.vertexes[cur_data_obj.facets[i] * 3 + 1], 
        cur_data_obj.vertexes[cur_data_obj.facets[i] * 3 + 2]
      );
  }
  glEnd();
}

void GLWidget::initialize_model() {
  s21::ReadOne* read = new s21::ReadOne();
  s21::ReadTwo* read2 = new s21::ReadTwo();
  s21::Parser parser(read);
  s21::DataObj data_info;
  s21::Transform transform;
  parser.ReadFile(modelPath.toStdString(), &data_info);
  parser.setStrategy(read2);
  parser.ReadFile(modelPath.toStdString(), &data_info);

  if (model != nullptr) {
    delete model;
  }
  model = new s21::Model(data_info, transform);
  
  if (pos_settings != nullptr) {
    delete pos_settings;
  }
  pos_settings = new s21::PositionModelSettings();

  pos_settings->Attach(model); 

  update();
}


void GLWidget::on_rotation_x_spinbox_valueChanged(double arg1) {
  pos_settings->SetAngleX(arg1);
  update();
}

void GLWidget::on_rotation_y_spinbox_valueChanged(double arg1) {
  pos_settings->SetAngleY(arg1);
  update();
}

void GLWidget::on_rotation_z_spinbox_valueChanged(double arg1) {
  pos_settings->SetAngleZ(arg1);
  update();
}

void GLWidget::on_position_x_spinbox_valueChanged(double arg1) {
  pos_settings->SetPosX(arg1);
  update();
}

void GLWidget::on_position_y_spinbox_valueChanged(double arg1) {
  pos_settings->SetPosY(arg1);
  update();
}

void GLWidget::on_position_z_spinbox_valueChanged(double arg1) {
  pos_settings->SetPosZ(arg1);
  update();
}

void GLWidget::on_model_scale_slider_valueChanged(int arg1) {
  pos_settings->SetScale(arg1);
  update();
}

void GLWidget::change_vertices_color() {
  QColor new_color = QColorDialog::getColor(Qt::white, this, tr("Vertices Color:"));
  global_settings.SetHigthColor(new_color);
  update();
}

void GLWidget::change_edges_color() {
  QColor new_color = QColorDialog::getColor(Qt::white, this, tr("Vertices Color:"));
  global_settings.SetEdgeColor(new_color);
  update();
}

void GLWidget::change_background_color() {
  QColor new_bg = QColorDialog::getColor(Qt::black, this, tr("Background Color:"));
  if (new_bg.isValid()) {
    global_settings.SetBackgroundColor(new_bg);
    update();
  }
}

void GLWidget::set_edges_type(int type) { //need to see
  global_settings.SetEdgesType(type);
  update();
}

void GLWidget::set_line_width(int size) {
  global_settings.SetEdgesSize(size/10.0);
  update();
}

void GLWidget::set_vertices_method(int type) {
  global_settings.SetVerticesDisplayMethod(type);
  update();
}

void GLWidget::set_vertices_size(int size) {
  global_settings.SetHigthSize(size);
  update();
}

void GLWidget::set_projection_type(int type) {
  global_settings.SetProectionType(type);
  update();
}
