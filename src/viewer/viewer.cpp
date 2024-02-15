#include "viewer.h"

#include "./ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui(new Ui::Viewer) {
  ui->setupUi(this);
  // glWidget = ui->widget;
  // settings = new QSettings(this);
  // load_settings();

  // connects
  connect(ui->vertices_color_btn, SIGNAL(clicked()), ui->widget, SLOT(change_vertices_color()));
  connect(ui->edges_color_btn, SIGNAL(clicked()), ui->widget, SLOT(change_edges_color()));
  connect(ui->background_color_btn, SIGNAL(clicked()), ui->widget, SLOT(change_background_color()));

  connect(ui->edges_type_combobox, SIGNAL(currentIndexChanged(int)), ui->widget, SLOT(set_edges_type(int)));
  connect(ui->projection_type_combobox, SIGNAL(currentIndexChanged(int)), ui->widget, SLOT(set_projection_type(int)));
  connect(ui->vertices_display_method_combobox, SIGNAL(currentIndexChanged(int)), ui->widget, SLOT(set_vertices_method(int))); // add 

  connect(ui->edges_thikness_slider, SIGNAL(valueChanged(int)), ui->widget, SLOT(set_line_width(int))); 
  connect(ui->vertices_size_slider, SIGNAL(valueChanged(int)), ui->widget, SLOT(set_vertices_size(int)));

  connect(ui->rotation_x_spinbox, SIGNAL(valueChanged(double)), ui->widget, SLOT(on_rotation_x_spinbox_valueChanged(double)));
  connect(ui->rotation_y_spinbox, SIGNAL(valueChanged(double)), ui->widget, SLOT(on_rotation_y_spinbox_valueChanged(double)));
  connect(ui->rotation_z_spinbox, SIGNAL(valueChanged(double)), ui->widget, SLOT(on_rotation_z_spinbox_valueChanged(double)));

  connect(ui->position_x_spinbox, SIGNAL(valueChanged(double)), ui->widget, SLOT(on_position_x_spinbox_valueChanged(double)));
  connect(ui->position_y_spinbox, SIGNAL(valueChanged(double)), ui->widget, SLOT(on_position_y_spinbox_valueChanged(double)));
  connect(ui->position_z_spinbox, SIGNAL(valueChanged(double)), ui->widget, SLOT(on_position_z_spinbox_valueChanged(double)));
  
  connect(ui->model_scale_slider, SIGNAL(valueChanged(int)), ui->widget, SLOT(on_model_scale_slider_valueChanged(int)));
}

Viewer::~Viewer() { delete ui; }

void Viewer::on_load_from_file_btn_clicked() {
  QString path =
      QFileDialog::getOpenFileName(this, "Load a file", QDir::currentPath());
  if (!path.isEmpty()) {
    QFileInfo fileInfo(path);
    if (fileInfo.suffix() != "obj") {
      QMessageBox::warning(this, "Warning!",
                           "Invalid file extension. Expected '.obj'");
    } else {
      ui->widget->modelPath = path;
      QString filename = fileInfo.fileName();
      ui->Filename_Label->setText(filename);
      ui->widget->initialize_model();

      ui->edges_count_label->setText(
          QString::number(ui->widget->model->GetData().count_edges));
      ui->vertices_count_label->setText(
          QString::number(ui->widget->model->GetData().count_vertex));
    }
  }
}
