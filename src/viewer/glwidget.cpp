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
}

void GLWidget::resizeGL(int width, int height) {
  glViewport(0, 0, height, width);
}

void GLWidget::paintGL() {
  // glMatrixMode(GL_PROJECTION);
  // glClearColor(background.redF(), background.greenF(), background.blueF(), 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  // glLoadIdentity();
  // if (projection_type == ProjectionType::CENTRAL) {
  //   gluPerspective(70.0, 1.5, 0.1, 50);
  // } else
    glOrtho(-5, 5, -5, 5, -100, 100);
  gluLookAt(2, 2, 4, 0, 0, 0, 0, 1, 0);

  glEnable(GL_PROGRAM_POINT_SIZE);

  // if (vetr_method == VerticesDisplayMethod::CIRCLE) {
  //   glEnable(GL_POINT_SMOOTH);
  //   glPointSize(vertices_size);
  // } else if (vetr_method == VerticesDisplayMethod::BLANK) {
  //   glPointSize(1);
  //   glDisable(GL_POINT_SMOOTH);
  // } else {
  //   glPointSize(vertices_size);
  //   glDisable(GL_POINT_SMOOTH);
  // }

  // TURNE
  // point *current_point_array = (point *)malloc(point_array_len * sizeof(point));
  // for (int i = 0; i < point_array_len; i++) {
  //   current_point_array[i] = point_array[i];
  //   rotate_around_axis(&current_point_array[i].x, &current_point_array[i].y,
  //                      current_angle_x);
  //   rotate_around_axis(&current_point_array[i].y, &current_point_array[i].z,
  //                      current_angle_y);
  //   rotate_around_axis(&current_point_array[i].x, &current_point_array[i].z,
  //                      current_angle_z);
  // }

  glBegin(GL_POINTS);
  // int loc_counter = 0;
  if(model != nullptr) {
    for (unsigned int i = 0; i < model->GetDataP()->count_vertex * 3; i += 3) {
      // glColor3f(vertices_color.redF(), vertices_color.greenF(),
      //           vertices_color.blueF());
      glVertex3f(
          model->GetDataP()->vertexes[i] * pos_settings->GetScale() + pos_settings->GetPosX(),
          model->GetDataP()->vertexes[i + 1] * pos_settings->GetScale() + pos_settings->GetPosY(),
          model->GetDataP()->vertexes[i + 2] * pos_settings->GetScale() + pos_settings->GetPosZ()
      );
      // glVertex3f(
      //     current_point_array[i].x * scale + position_x,
      //     current_point_array[i].y * scale + position_y,
      //     current_point_array[i].z * scale + position_z);
    }
  }
  glEnd();

  // if (edges_type == EdgesType::DASHED) {
  //   glEnable(GL_LINE_STIPPLE);
  // } else {
  //   glDisable(GL_LINE_STIPPLE);
  // }
  // glLineStipple(3, 0xDDDD);

  // glLineWidth(line_width);

  glBegin(GL_LINES);
  // glColor3f(edges_color.redF(), edges_color.greenF(), edges_color.blueF());
  // loc_counter = 0;
  if (model != nullptr) {
    for (unsigned int i = 0; i < model->GetDataP()->count_facets * 2; ++i) {
        glVertex3f(
          model->GetDataP()->vertexes[model->GetDataP()->facets[i] * 3] * pos_settings->GetScale() + pos_settings->GetPosX(),
          model->GetDataP()->vertexes[model->GetDataP()->facets[i] * 3 + 1] * pos_settings->GetScale() + pos_settings->GetPosY(), 
          model->GetDataP()->vertexes[model->GetDataP()->facets[i] * 3 + 2] * pos_settings->GetScale() + pos_settings->GetPosZ()
        );
        // glVertex3f(
        //   model->GetDataP()->vertexes[model->GetDataP()->facets[i]] * pos_settings->GetScale(),
        //   model->GetDataP()->vertexes[model->GetDataP()->facets[i] + 1] * pos_settings->GetScale(), 
        //   model->GetDataP()->vertexes[model->GetDataP()->facets[i] + 2] * pos_settings->GetScale()
        // );
        // loc_counter++;

      // glVertex3f(current_point_array[line_array[i].a - 1].x * scale + position_x,
      //            current_point_array[line_array[i].a - 1].y * scale + position_y,
      //            current_point_array[line_array[i].a - 1].z * scale + position_z);


      // glVertex3f(current_point_array[line_array[i].b - 1].x * scale + position_x,
      //            current_point_array[line_array[i].b - 1].y * scale + position_y,
      //            current_point_array[line_array[i].b - 1].z * scale + position_z);
    }
  }
  glEnd();
  // drawAxis();
  // free(current_point_array);
}

// void GLWidget::drawAxis() {
//   glBegin(GL_LINES);
//   glColor3f(0.0, 0.0, 1.0);
//   glVertex3f(0, 0, 0);
//   glVertex3f(.5, 0, 0);
//   glEnd();

//   glBegin(GL_LINES);
//   glColor3f(0.0, 1.0, 0.0);
//   glVertex3f(0, 0, 0);
//   glVertex3f(0, .5, 0);
//   glEnd();

//   glBegin(GL_LINES);
//   glColor3f(1.0, 0.0, 0.0);
//   glVertex3f(0, 0, 0);
//   glVertex3f(0, 0, .5);
//   glEnd();
// }

// void GLWidget::set_vertices_size(int value) {
//   vertices_size = value;
//   update();
// }

// void GLWidget::set_vertices_color(QColor new_color) {
//   vertices_color = new_color;
//   update();
// }

// void GLWidget::set_edges_color(QColor new_color) {
//   edges_color = new_color;
//   update();
// }

// void GLWidget::set_vertices_method(int value) {
//   vetr_method = VerticesDisplayMethod(value);
//   update();
// }

// void GLWidget::set_edges_type(int value) {
//   edges_type = EdgesType(value);
//   update();
// }

// void GLWidget::set_line_width(int value) {
//   line_width = value;
//   update();
// }

// void GLWidget::set_projection_type(int type) {
//   projection_type = ProjectionType(type);
//   update();
// }

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

  pos_settings->Attach(model); // Error


  // point gravity_center = {.x = 0, .y = 0, .z = 0};

//  delete read;
//  delete read2;

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
  pos_settings->SetScale(arg1/10.0);
  update();
}
