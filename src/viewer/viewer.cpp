#include "viewer.h"

#include "./ui_viewer.h"

Viewer::Viewer(QWidget *parent) : QMainWindow(parent), ui(new Ui::Viewer) {
  ui->setupUi(this);
  // glWidget = ui->widget;
  // settings = new QSettings(this);
  // load_settings();

  // connects
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

      // ui->edges_count_label->setText(
      //     QString::number(ui->widget->get_edges_count()));
      // ui->vertices_count_label->setText(
      //     QString::number(ui->widget->get_points_count()));
    }
  }
}
