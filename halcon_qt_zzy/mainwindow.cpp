#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QSize>
#include <QMessageBox>
#include <QCloseEvent>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);   //定时器连接相机循环函数

    connect(timer,SIGNAL(timeout()),this,SLOT(camera()));
    // connect(ui->pushButton_stop,SIGNAL(clicked(bool)),qApp,SLOT(quit()));
    Path="dog.jpg";
    Pathncc = "dog.jpg";
    Pathfileshape = "tubiao1.jpg";
    stop_msg = "ok";
    camera_video = "[0] XiaoMi USB 2.0 Webcam";
    image_field = "F:/abc.jpg";
    image_style = "jpg";
    Threshold1 = 0;
    Threshold2 = 255;
    shape1 = 0;
    shape2 = 255;
    shapearea1 = 0;
    shapearea2 = 20000000;
    scale1 = 0;
    scale2 = 1.0;
    emphasize_msg1 = 1.0;
    emphasize_msg2 = "7";
    t = "no";
    s = "no";
    scale_msg = "no";
    emphasize1 = "no";
    nccmsg = "no";
    shapemsg = "no";
    ReadImage(&ho_image, Path.toStdString().c_str());

    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_gray->setEnabled(false);
    ui->pushButton_save->setEnabled(false);
    ui->pushButton_clear->setEnabled(false);
    ui->pushButton_Threshold1->setEnabled(false);
    ui->pushButton_emphasize1->setEnabled(false);
    ui->pushButton_emphasize2->setEnabled(false);
    ui->pushButton_drawcircle->setEnabled(false);
    ui->pushButton_line->setEnabled(false);
    ui->pushButton_Rectangle1->setEnabled(false);
    ui->pushButton_Rectangle2->setEnabled(false);
    ui->pushButton_Ellipse->setEnabled(false);
    ui->pushButton_Polygon->setEnabled(false);
    ui->pushButton_scale->setEnabled(false);
    ui->pushButton_Threshold2->setEnabled(false);
    ui->horizontalSlider_Threshold1->setEnabled(false);
    ui->horizontalSlider_Threshold2->setEnabled(false);
    ui->horizontalSlider_scale1->setEnabled(false);
    ui->comboBox_emphasize->setEnabled(false);
    ui->doubleSpinBox_emphasize->setEnabled(false);
    ui->doubleSpinBox_scale->setEnabled(false);
    ui->pushButton_draw->setEnabled(false);
    ui->pushButton_scale1->setEnabled(false);
    ui->pushButton_nccclear->setEnabled(false);
    ui->pushButton_creatncc->setEnabled(false);
    ui->pushButton_findimage->setEnabled(false);
    ui->pushButton_findncc->setEnabled(false);
    ui->pushButton_clearshape->setEnabled(false);
    ui->horizontalSlider_choiceshape1->setEnabled(false);
    ui->horizontalSlider_choiceshape2->setEnabled(false);
    ui->horizontalSlider_choiceshape3->setEnabled(false);
    ui->horizontalSlider_choiceshape4->setEnabled(false);
    ui->pushButton_choiceshape->setEnabled(false);
    ui->pushButton_choiceshape1->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_createshape->setEnabled(false);
    ui->pushButton_18->setEnabled(false);
    ui->pushButton_shapefind->setEnabled(false);

    statusBar = new QStatusBar(this);   // 创建底部状态栏对象
    setStatusBar(statusBar); // 设置窗口的状态栏
    statusBar->setStyleSheet("QStatusBar {"
                             "color: blue;" // 设置字体颜色为红色
                             // "background-color: black;" // 设置背景颜色为黑色
                             "}");
    // 设置滑动条范围从0到255
    ui->horizontalSlider_Threshold1->setRange(0, 255);
    ui->horizontalSlider_Threshold1->setValue(0);     // 设置初始值为0
    ui->horizontalSlider_Threshold1->setSingleStep(1); // 设置步长为1
    ui->horizontalSlider_Threshold2->setRange(0, 255);
    ui->horizontalSlider_Threshold2->setValue(255);     // 设置初始值为255
    ui->horizontalSlider_Threshold2->setSingleStep(1); // 设置步长为1

    ui->horizontalSlider_choiceshape1->setRange(0, 255);
    ui->horizontalSlider_choiceshape1->setValue(0);     // 设置初始值为255
    ui->horizontalSlider_choiceshape1->setSingleStep(1); // 设置步长为1
    ui->horizontalSlider_choiceshape2->setRange(0, 255);
    ui->horizontalSlider_choiceshape2->setValue(255);     // 设置初始值为255
    ui->horizontalSlider_choiceshape2->setSingleStep(1); // 设置步长为1

    ui->horizontalSlider_choiceshape3->setRange(0, 2000000);
    ui->horizontalSlider_choiceshape3->setValue(0);     // 设置初始值为255
    ui->horizontalSlider_choiceshape3->setSingleStep(1); // 设置步长为1
    ui->horizontalSlider_choiceshape4->setRange(0, 2000000);
    ui->horizontalSlider_choiceshape4->setValue(2000000);     // 设置初始值为255
    ui->horizontalSlider_choiceshape4->setSingleStep(1); // 设置步长为1

    ui->horizontalSlider_scale1->setRange(-200, 100);
    ui->horizontalSlider_scale1->setValue(0);     // 设置初始值为0
    ui->horizontalSlider_scale1->setSingleStep(1); // 设置步长为1

    // 对比度控件设置
    ui->doubleSpinBox_emphasize->setDecimals(1); // 设置显示1位小数
    ui->doubleSpinBox_emphasize->setValue(1.0); // 设置初始值为1.0
    ui->doubleSpinBox_emphasize->setSingleStep(0.1); // 设置步长为0.1
    ui->doubleSpinBox_scale->setRange(0.00,5.00);  //范围
    ui->doubleSpinBox_scale->setDecimals(2);   //显示一位小数
    ui->doubleSpinBox_scale->setValue(1.0);    //初始值
    ui->doubleSpinBox_scale->setSingleStep(0.05);  //步长

    ui->doubleSpinBox_nccjindu->setRange(0.00,1.00);  //范围
    ui->doubleSpinBox_nccjindu->setDecimals(2);   //显示一位小数
    ui->doubleSpinBox_nccjindu->setValue(0.50);    //初始值
    ui->doubleSpinBox_nccjindu->setSingleStep(0.01);  //步长
    ui->doubleSpinBox_nccchongdie->setRange(0.0,1.0);  //范围
    ui->doubleSpinBox_nccchongdie->setDecimals(1);   //显示一位小数
    ui->doubleSpinBox_nccchongdie->setValue(0.2);    //初始值
    ui->doubleSpinBox_nccchongdie->setSingleStep(0.1);  //步长

    ui->doubleSpinBox_shapemin->setRange(0.0,1.0);  //范围
    ui->doubleSpinBox_shapemin->setDecimals(1);   //显示一位小数
    ui->doubleSpinBox_shapemin->setValue(0.2);    //初始值
    ui->doubleSpinBox_shapemin->setSingleStep(0.1);  //步长
    ui->doubleSpinBox_shapemax->setRange(1.0,2.0);  //范围
    ui->doubleSpinBox_shapemax->setDecimals(1);   //显示一位小数
    ui->doubleSpinBox_shapemax->setValue(1.1);    //初始值
    ui->doubleSpinBox_shapemax->setSingleStep(0.1);  //步长
    ui->doubleSpinBox_shapejindu->setRange(0.00,1.00);  //范围
    ui->doubleSpinBox_shapejindu->setDecimals(2);   //显示一位小数
    ui->doubleSpinBox_shapejindu->setValue(0.3);    //初始值
    ui->doubleSpinBox_shapejindu->setSingleStep(0.01);  //步长
    ui->doubleSpinBox_shapechongdie->setRange(0.0,1.0);  //范围
    ui->doubleSpinBox_shapechongdie->setDecimals(1);   //显示一位小数
    ui->doubleSpinBox_shapechongdie->setValue(0.5);    //初始值
    ui->doubleSpinBox_shapechongdie->setSingleStep(0.1);  //步长

}

MainWindow::~MainWindow()
{
    delete ui;
}
//获取图片地址按键
void MainWindow::on_pushButton_image_file_clicked()
{
    // Path=ui->image_file->text();
    // QMessageBox::information(this,"提示",Path);
    Path = QFileDialog::getOpenFileName(this,"文件夹：","/");
    ui->image_file->setText(Path);
}

void MainWindow::on_pushButton_2_clicked()
{
    CloseWindow(hv_WindowHandle);   //关闭当前窗口
    winId_image = (Hlong)this->ui->graphicsView_image->winId();  //绑定窗口
    ReadImage(&ho_image, Path.toStdString().c_str());  //读取图片
    GetImageSize(ho_image, &hv_Width, &hv_Height);  //获取图片尺寸
    OpenWindow(0,0,ui->graphicsView_image->width(),ui->graphicsView_image->height(),winId_image,"visible","",&hv_WindowHandle);  // 打开窗口
    SetWindowAttr("background_color","black");  // 设置背景颜色
    SetLineWidth(hv_WindowHandle,3);
    SetPart(hv_WindowHandle,0, 0, hv_Height-1, hv_Width - 1);  //设置图像显示为充满图像
    DispObj(ho_image, hv_WindowHandle);  // 显示图片
    ui->pushButton_gray->setEnabled(true);
    ui->pushButton_save->setEnabled(true);
    ui->pushButton_clear->setEnabled(true);
    ui->pushButton_emphasize1->setEnabled(true);
    ui->pushButton_scale->setEnabled(true);
    ui->pushButton_Threshold1->setEnabled(true);
    ui->pushButton_draw->setEnabled(true);
    statusBar->showMessage(Path+":图片已载入窗口！");
    QSize size = ui->graphicsView_image->size();  //窗口大小
    QString sizeStr = QString("%1x%2").arg(size.width()).arg(size.height());
    ui->label_windowsize->setText(sizeStr);
}

void MainWindow::on_pushButton_0_video_clicked()
{
    set_camera=ui->lineEdit_video0->text();  // XiaoMi USB 2.0 Webcam
    camera_video = "[0] " + set_camera;
    qDebug() << camera_video;
    QMessageBox::information(this,"提示","已添加外设摄像头:"+camera_video);
}

void MainWindow::on_pushButton_3_clicked()
{
    timer->start(20);//定时器开始工作,参数影响帧率
    winId = (Hlong)this->ui->GV_window->winId();  // 绑定窗口
    CloseWindow(hv_WindowHandle1);  //关闭当前窗口
    OpenFramegrabber("DirectShow", 1, 1, 0, 0, 0, 0, "default", 8, "rgb", -1, "false",      //摄像头参数配置
                     "default", camera_video.toStdString().c_str(), 0, -1, &hv_AcqHandle);
    GrabImageStart(hv_AcqHandle, -1);  // 启动一个异步的图像采集过程
    GrabImageAsync(&ho_camera, hv_AcqHandle, -1);  // 从指定的图像采集设备异步获取图像
    GetImageSize(ho_camera, &hv_Width1, &hv_Height1);  // 获取尺寸
    OpenWindow(0,0,ui->GV_window->width(),ui->GV_window->height(),winId,"visible","",&hv_WindowHandle1);  // 打开窗口
    SetPart(hv_WindowHandle1,0, 0, hv_Height1-1, hv_Width1 - 1);  //设置图像显示为充满图像
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_stop->setEnabled(true);
    ui->pushButton_0_video->setEnabled(false);
    ui->pushButton_1_video->setEnabled(false);
    stop_msg = "no";
}

void MainWindow::on_pushButton_stop_clicked()
{
    timer->stop();  // 定时器关闭
    CloseFramegrabber(hv_AcqHandle);  // 关闭图像采集
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_stop->setEnabled(false);
    ui->pushButton_0_video->setEnabled(true);
    ui->pushButton_1_video->setEnabled(true);
    stop_msg = "ok";
}

void MainWindow::camera()
{
    GrabImageAsync(&ho_camera, hv_AcqHandle, -1);  // 获取图像
    SetPart(hv_WindowHandle1,0, 0, hv_Height1-1, hv_Width1 - 1);
    DispObj(ho_camera,hv_WindowHandle1);  // 显示图像
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(nccmsg == "ok"){
        ClearNccModel(hv_nccModelID);
        nccmsg = "no";
    }
    if(shapemsg == "ok"){
        ClearShapeModel(hv_ModelIDshape);
        shapemsg = "no";
    }
    int ret = QMessageBox::question(this, "询问", "是否退出？",
                                    QMessageBox::Yes | QMessageBox::No,
                                    QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        if (stop_msg == "ok"){
            event->accept();
        }else {
            QMessageBox::information(this,"提示","摄像头未结束获取");
            event->ignore();
        }
    } else {
        event->ignore();  // 用户点击了“否”
    }
}

void MainWindow::on_pushButton_1_video_clicked()
{
    set_camera=ui->lineEdit_video1->text();
    camera_video = "[1] " + set_camera;
    QMessageBox::information(this,"提示","已添加外设摄像头:"+camera_video);
}

void MainWindow::on_pushButton_clear_clicked()
{
    CloseWindow(hv_WindowHandle);
    ui->pushButton_gray->setEnabled(false);
    ui->pushButton_save->setEnabled(false);
    ui->pushButton_clear->setEnabled(false);
    ui->pushButton_Threshold1->setEnabled(false);
    ui->pushButton_emphasize1->setEnabled(false);
    ui->pushButton_emphasize2->setEnabled(false);
    ui->pushButton_drawcircle->setEnabled(false);
    ui->pushButton_line->setEnabled(false);
    ui->pushButton_Rectangle1->setEnabled(false);
    ui->pushButton_Rectangle2->setEnabled(false);
    ui->pushButton_Ellipse->setEnabled(false);
    ui->pushButton_Polygon->setEnabled(false);
    ui->pushButton_scale->setEnabled(false);
    ui->pushButton_scale1->setEnabled(false);
    ui->pushButton_Threshold2->setEnabled(false);
    ui->pushButton_draw->setEnabled(false);
    ui->horizontalSlider_Threshold2->setEnabled(false);
    ui->horizontalSlider_Threshold1->setEnabled(false);
    ui->comboBox_emphasize->setEnabled(false);
    ui->doubleSpinBox_emphasize->setEnabled(false);
    ui->horizontalSlider_scale1->setEnabled(false);
    ui->doubleSpinBox_scale->setEnabled(false);
    statusBar->showMessage("窗口已清理！");
    t = "no";
    scale_msg = "no";
    emphasize1 = "no";
}
// 转灰度图
void MainWindow::on_pushButton_gray_clicked()
{
    Rgb1ToGray(ho_image, &ho_image);
    DispObj(ho_image, hv_WindowHandle);
    ui->pushButton_Threshold1->setEnabled(true);
    statusBar->showMessage("已生成灰度图.");
}
// 获取图片路径
void MainWindow::on_pushButton_save_clicked()
{
    image_field = ui->lineEdit_field->text();
    image_style = ui->lineEdit_style->text();
    WriteImage(ho_image, image_style.toStdString().c_str(), 0, image_field.toStdString().c_str());
    statusBar->showMessage("图片已保存至:"+image_field);
}
// 阈值
void MainWindow::on_horizontalSlider_Threshold1_valueChanged(int value1)
{
    Threshold1 = value1;
    Threshold_msg1 = QString("%1").arg(value1);
    ui->label_Threshold1->setText(Threshold_msg1);
    Threshold_color = ui->comboBox_threshold->currentText(); // 获取当前选中的文本
    if( Threshold1 < Threshold2){  // 判断是否有交叉
        if(t == "ok"){
            ClearWindow(hv_WindowHandle);  // 清理当前窗口
            Threshold(ho_image, &ho_Regions, Threshold1, Threshold2);
            SetColor(hv_WindowHandle,Threshold_color.toStdString().c_str());
            DispObj(ho_Regions, hv_WindowHandle);
            statusBar->showMessage("二值化选定区域颜色:"+Threshold_color);
            ui->pushButton_Threshold2->setEnabled(true);
        }
    }else{
        Threshold2 = Threshold1 + 1;
        ui->horizontalSlider_Threshold2->setValue(Threshold2);
    }
}

void MainWindow::on_horizontalSlider_Threshold2_valueChanged(int value2)
{
    Threshold2 = value2;
    Threshold_msg2 = QString("%1").arg(value2);
    ui->label_Threshold2->setText(Threshold_msg2);
    Threshold_color = ui->comboBox_threshold->currentText(); // 获取当前选中的文本
    if(Threshold1 < Threshold2){
        if(t == "ok"){
            ClearWindow(hv_WindowHandle);  // 关闭当前窗口
            Threshold(ho_image, &ho_Regions, Threshold1, Threshold2);
            SetColor(hv_WindowHandle,Threshold_color.toStdString().c_str());
            DispObj(ho_Regions, hv_WindowHandle);
            statusBar->showMessage("二值化选定区域颜色:"+Threshold_color);
            ui->pushButton_Threshold2->setEnabled(true);
        }
    }else{
        Threshold1 = Threshold2 - 1;
        ui->horizontalSlider_Threshold1->setValue(Threshold1);
    }
}

void MainWindow::on_pushButton_Threshold1_clicked()
{
    t = "ok";
    statusBar->showMessage("二值化已打开.");
    ui->horizontalSlider_Threshold2->setEnabled(true);
    ui->horizontalSlider_Threshold1->setEnabled(true);
}

void MainWindow::on_pushButton_Threshold2_clicked()
{
    RegionToMean(ho_Regions, ho_image, &ho_image);  // 将二值化区域生成图像
    statusBar->showMessage("二值化已完成并推出.");
    ui->pushButton_Threshold2->setEnabled(false);
    ui->horizontalSlider_Threshold2->setEnabled(false);
    ui->horizontalSlider_Threshold1->setEnabled(false);
}

void MainWindow::on_pushButton_emphasize1_clicked()
{
    emphasize1 = "ok";
    ui->pushButton_emphasize2->setEnabled(true);
    ui->comboBox_emphasize->setEnabled(true);
    ui->doubleSpinBox_emphasize->setEnabled(true);
    statusBar->showMessage("已开启对比度调节,初始强度1.0,掩码7x7.");
}

void MainWindow::on_pushButton_emphasize2_clicked()
{
    ho_image = ho_ImageEmphasize;
    QString ccc = ui->doubleSpinBox_emphasize->text();
    statusBar->showMessage("强度"+ccc+",掩码"+emphasize_msg2+"x"+emphasize_msg2);
    ui->pushButton_emphasize2->setEnabled(false);
    ui->comboBox_emphasize->setEnabled(false);
    ui->doubleSpinBox_emphasize->setEnabled(false);
}

void MainWindow::on_comboBox_emphasize_currentTextChanged(const QString &arg3)
{
    emphasize_msg2 = arg3;
    if(emphasize1 == "ok"){
        Emphasize(ho_image, &ho_ImageEmphasize, emphasize_msg2.toInt(), emphasize_msg2.toInt(), emphasize_msg1);
        DispObj(ho_ImageEmphasize, hv_WindowHandle);
    }
}

void MainWindow::on_doubleSpinBox_emphasize_valueChanged(double arg2)
{
    emphasize_msg1 = arg2;
    if(emphasize1 == "ok"){
        Emphasize(ho_image, &ho_ImageEmphasize, emphasize_msg2.toInt(), emphasize_msg2.toInt(), emphasize_msg1);
        DispObj(ho_ImageEmphasize, hv_WindowHandle);
    }
}

void MainWindow::on_pushButton_draw_clicked()
{
    SetDraw(hv_WindowHandle,"margin");
    ui->pushButton_drawcircle->setEnabled(true);
    ui->pushButton_line->setEnabled(true);
    ui->pushButton_Rectangle1->setEnabled(true);
    ui->pushButton_Rectangle2->setEnabled(true);
    ui->pushButton_Polygon->setEnabled(true);
    ui->pushButton_Ellipse->setEnabled(true);
}

void MainWindow::on_pushButton_drawcircle_clicked()
{
    ui->pushButton_drawcircle->setEnabled(false);
    ui->pushButton_line->setEnabled(false);
    ui->pushButton_Rectangle1->setEnabled(false);
    ui->pushButton_Rectangle2->setEnabled(false);
    ui->pushButton_Ellipse->setEnabled(false);
    ui->pushButton_Polygon->setEnabled(false);
    statusBar->showMessage("左键按下开始绘制圆,右键点击完成绘制.");
    draw_color = ui->comboBox_drawcolor->currentText(); // 获取当前选中的文本
    SetColor(hv_WindowHandle,draw_color.toStdString().c_str()); //设置颜色
    DrawCircle(hv_WindowHandle, &hv_Row, &hv_Column, &hv_Radius);
    GenCircle(&ho_Circle, hv_Row, hv_Column, hv_Radius);
    DispObj(ho_Circle, hv_WindowHandle);
    PaintRegion(ho_Circle, ho_image, &ho_image, ((HTuple(255).Append(0)).Append(0)), "margin");
    statusBar->showMessage("圆绘制完成！");
    ui->pushButton_drawcircle->setEnabled(true);
    ui->pushButton_line->setEnabled(true);
    ui->pushButton_Rectangle1->setEnabled(true);
    ui->pushButton_Rectangle2->setEnabled(true);
    ui->pushButton_Ellipse->setEnabled(true);
    ui->pushButton_Polygon->setEnabled(true);
}

void MainWindow::on_pushButton_line_clicked()
{
    ui->pushButton_drawcircle->setEnabled(false);
    ui->pushButton_line->setEnabled(false);
    ui->pushButton_Rectangle1->setEnabled(false);
    ui->pushButton_Rectangle2->setEnabled(false);
    ui->pushButton_Ellipse->setEnabled(false);
    ui->pushButton_Polygon->setEnabled(false);
    statusBar->showMessage("左键按下开始绘制直线，右键点击完成绘制.");
    draw_color = ui->comboBox_drawcolor->currentText(); // 获取当前选中的文本
    SetColor(hv_WindowHandle,draw_color.toStdString().c_str()); //设置颜色
    DrawLine(hv_WindowHandle, &hv_Row1, &hv_Column1, &hv_Row2, &hv_Column2);
    GenRegionLine(&ho_RegionLines, hv_Row1, hv_Column1, hv_Row2, hv_Column2);
    DispObj(ho_RegionLines, hv_WindowHandle);
    PaintRegion(ho_RegionLines, ho_image, &ho_image, ((HTuple(255).Append(0)).Append(0)), "margin");
    statusBar->showMessage("直线绘制完成!");
    ui->pushButton_drawcircle->setEnabled(true);
    ui->pushButton_line->setEnabled(true);
    ui->pushButton_Rectangle1->setEnabled(true);
    ui->pushButton_Rectangle2->setEnabled(true);
    ui->pushButton_Ellipse->setEnabled(true);
    ui->pushButton_Polygon->setEnabled(true);
}

void MainWindow::on_pushButton_Rectangle1_clicked()
{
    ui->pushButton_drawcircle->setEnabled(false);
    ui->pushButton_line->setEnabled(false);
    ui->pushButton_Rectangle1->setEnabled(false);
    ui->pushButton_Rectangle2->setEnabled(false);
    ui->pushButton_Ellipse->setEnabled(false);
    ui->pushButton_Polygon->setEnabled(false);
    statusBar->showMessage("左键按下开始绘制矩形，右键点击完成绘制.");
    draw_color = ui->comboBox_drawcolor->currentText(); // 获取当前选中的文本
    SetColor(hv_WindowHandle,draw_color.toStdString().c_str()); //设置颜色
    DrawRectangle1(hv_WindowHandle, &hv_Row11, &hv_Column11, &hv_Row21, &hv_Column21);
    GenRectangle1(&ho_Rectangle, hv_Row11, hv_Column11, hv_Row21, hv_Column21);
    DispObj(ho_Rectangle, hv_WindowHandle);
    PaintRegion(ho_Rectangle, ho_image, &ho_image, ((HTuple(255).Append(0)).Append(0)), "margin");
    statusBar->showMessage("矩形绘制完成!");
    ui->pushButton_drawcircle->setEnabled(true);
    ui->pushButton_line->setEnabled(true);
    ui->pushButton_Rectangle1->setEnabled(true);
    ui->pushButton_Rectangle2->setEnabled(true);
    ui->pushButton_Ellipse->setEnabled(true);
    ui->pushButton_Polygon->setEnabled(true);
}

void MainWindow::on_pushButton_Rectangle2_clicked()
{
    ui->pushButton_drawcircle->setEnabled(false);
    ui->pushButton_line->setEnabled(false);
    ui->pushButton_Rectangle1->setEnabled(false);
    ui->pushButton_Rectangle2->setEnabled(false);
    ui->pushButton_Ellipse->setEnabled(false);
    ui->pushButton_Polygon->setEnabled(false);
    statusBar->showMessage("左键按下开始绘制矩形，右键点击完成绘制.");
    draw_color = ui->comboBox_drawcolor->currentText(); // 获取当前选中的文本
    SetColor(hv_WindowHandle,draw_color.toStdString().c_str()); //设置颜色
    DrawRectangle2(hv_WindowHandle, &hv_Row4, &hv_Column4, &hv_Phi1, &hv_Length1, &hv_Length2);
    GenRectangle2(&ho_Rectangle1, hv_Row4, hv_Column4, hv_Phi1, hv_Length1, hv_Length2);
    DispObj(ho_Rectangle1, hv_WindowHandle);
    PaintRegion(ho_Rectangle1, ho_image, &ho_image, ((HTuple(255).Append(0)).Append(0)), "margin");
    statusBar->showMessage("矩形绘制完成!");
    ui->pushButton_drawcircle->setEnabled(true);
    ui->pushButton_line->setEnabled(true);
    ui->pushButton_Rectangle1->setEnabled(true);
    ui->pushButton_Rectangle2->setEnabled(true);
    ui->pushButton_Ellipse->setEnabled(true);
    ui->pushButton_Polygon->setEnabled(true);
}

void MainWindow::on_pushButton_Ellipse_clicked()
{
    ui->pushButton_drawcircle->setEnabled(false);
    ui->pushButton_line->setEnabled(false);
    ui->pushButton_Rectangle1->setEnabled(false);
    ui->pushButton_Rectangle2->setEnabled(false);
    ui->pushButton_Ellipse->setEnabled(false);
    ui->pushButton_Polygon->setEnabled(false);
    statusBar->showMessage("左键按下开始绘制椭圆，右键点击完成绘制.");
    draw_color = ui->comboBox_drawcolor->currentText(); // 获取当前选中的文本
    SetColor(hv_WindowHandle,draw_color.toStdString().c_str()); //设置颜色
    DrawEllipse(hv_WindowHandle, &hv_Row3, &hv_Column3, &hv_Phi, &hv_Radius1, &hv_Radius2);
    GenEllipse(&ho_Ellipse, hv_Row3, hv_Column3, hv_Phi, hv_Radius1, hv_Radius2);
    DispObj(ho_Ellipse, hv_WindowHandle);
    PaintRegion(ho_Ellipse, ho_image, &ho_image, ((HTuple(255).Append(0)).Append(0)), "margin");
    statusBar->showMessage("椭圆绘制完成!");
    ui->pushButton_drawcircle->setEnabled(true);
    ui->pushButton_line->setEnabled(true);
    ui->pushButton_Rectangle1->setEnabled(true);
    ui->pushButton_Rectangle2->setEnabled(true);
    ui->pushButton_Ellipse->setEnabled(true);
    ui->pushButton_Polygon->setEnabled(true);
}

void MainWindow::on_pushButton_Polygon_clicked()
{
    ui->pushButton_drawcircle->setEnabled(false);
    ui->pushButton_line->setEnabled(false);
    ui->pushButton_Rectangle1->setEnabled(false);
    ui->pushButton_Rectangle2->setEnabled(false);
    ui->pushButton_Ellipse->setEnabled(false);
    ui->pushButton_Polygon->setEnabled(false);
    statusBar->showMessage("左键按下开始绘制不规则图形,右键点击完成绘制.");
    draw_color = ui->comboBox_drawcolor->currentText(); // 获取当前选中的文本
    SetColor(hv_WindowHandle,draw_color.toStdString().c_str()); //设置颜色
    DrawPolygon(&ho_PolygonRegion, hv_WindowHandle);
    DispObj(ho_PolygonRegion, hv_WindowHandle);
    PaintRegion(ho_PolygonRegion, ho_image, &ho_image, ((HTuple(255).Append(0)).Append(0)), "margin");
    statusBar->showMessage("图形绘制完成!");
    ui->pushButton_drawcircle->setEnabled(true);
    ui->pushButton_line->setEnabled(true);
    ui->pushButton_Rectangle1->setEnabled(true);
    ui->pushButton_Rectangle2->setEnabled(true);
    ui->pushButton_Ellipse->setEnabled(true);
    ui->pushButton_Polygon->setEnabled(true);
}

void MainWindow::on_pushButton_scale_clicked()
{
    scale_msg = "ok";
    statusBar->showMessage("已开启亮度调节！");
    ui->pushButton_scale1->setEnabled(true);
    ui->doubleSpinBox_scale->setEnabled(true);
    ui->horizontalSlider_scale1->setEnabled(true);
}

void MainWindow::on_horizontalSlider_scale1_valueChanged(int value3)
{
    scale1 = value3;
    if(scale_msg == "ok"){
        ScaleImage(ho_image, &ho_ImageScaled, scale2, scale1);
        ClearWindow(hv_WindowHandle);
        DispObj(ho_ImageScaled, hv_WindowHandle);
    }
}

void MainWindow::on_doubleSpinBox_scale_valueChanged(double arg1)
{
    scale2 = arg1;
    if(scale_msg == "ok"){
        ScaleImage(ho_image, &ho_ImageScaled, scale2, scale1);
        ClearWindow(hv_WindowHandle);
        DispObj(ho_ImageScaled, hv_WindowHandle);
    }
}

void MainWindow::on_pushButton_scale1_clicked()
{
    ho_image = ho_ImageScaled;
    statusBar->showMessage("完成亮度调节,已退出！");
    ui->pushButton_scale1->setEnabled(false);
    ui->doubleSpinBox_scale->setEnabled(false);
    ui->horizontalSlider_scale1->setEnabled(false);
}

void MainWindow::on_pushButton_nccfile_clicked()
{
    // Pathncc = ui->lineEdit_ncc->text();
    // QMessageBox::information(this,"提示",Pathncc);
    Pathncc = QFileDialog::getOpenFileName(this,"文件夹：","/");
    ui->lineEdit_ncc->setText(Pathncc);
}

void MainWindow::on_pushButton_nccimage_clicked()
{
    CloseWindow(hv_WindowHandle2);  //关闭当前窗口
    winId_ncc = (Hlong)this->ui->graphicsView_ncc->winId();  //绑定窗口
    ReadImage(&ho_nccImage, Pathncc.toStdString().c_str());  //读取图片
    GetImageSize(ho_nccImage, &hv_Widthncc, &hv_Heightncc);  //获取图片尺寸
    OpenWindow(0,0,ui->graphicsView_ncc->width(),ui->graphicsView_ncc->height(),winId_ncc,"visible","",&hv_WindowHandle2); // 打开窗口
    SetWindowAttr("background_color","black"); // 设置背景颜色
    SetLineWidth(hv_WindowHandle2,3);
    SetPart(hv_WindowHandle2,0, 0, hv_Heightncc - 1, hv_Widthncc - 1); //设置图像显示为充满图像
    DispObj(ho_nccImage, hv_WindowHandle2); // 显示图片
    statusBar->showMessage(Pathncc+":图片已载入窗口！");
    ui->pushButton_nccclear->setEnabled(true);
    ui->pushButton_creatncc->setEnabled(true);
}

void MainWindow::on_pushButton_nccclear_clicked()
{
    if(nccmsg == "ok"){
        ClearNccModel(hv_nccModelID);
        ui->label_creatmsg->setText("模板为空.");
        nccmsg = "no";
    }
    CloseWindow(hv_WindowHandle2);
    statusBar->showMessage("窗口已清理！");
    ui->pushButton_nccclear->setEnabled(false);
    ui->pushButton_creatncc->setEnabled(false);
    ui->pushButton_findimage->setEnabled(false);
    ui->pushButton_findncc->setEnabled(false);

}

void MainWindow::on_pushButton_creatncc_clicked()
{
    ClearWindow(hv_WindowHandle2);
    DispObj(ho_nccImage,hv_WindowHandle2);
    SetDraw(hv_WindowHandle2,"margin"); // 设置画笔
    SetLineWidth(hv_WindowHandle2,3);
    SetColor(hv_WindowHandle2,"red");
    Rgb1ToGray(ho_nccImage, &ho_nccGrayImage);
    statusBar->showMessage("左键按下开始框选模板，右键点击完成框选！");
    ui->pushButton_nccclear->setEnabled(false);
    ui->pushButton_creatncc->setEnabled(false);
    ui->pushButton_nccimage->setEnabled(false);
    DrawRectangle1(hv_WindowHandle2, &hv_nccRow1, &hv_nccColumn1, &hv_nccRow2, &hv_nccColumn2); //画矩形
    GenRectangle1(&ho_nccRectangle, hv_nccRow1, hv_nccColumn1, hv_nccRow2, hv_nccColumn2);
    DispObj(ho_nccRectangle, hv_WindowHandle2);
    ReduceDomain(ho_nccGrayImage, ho_nccRectangle, &ho_nccImageReduced); //抠图
    //创建ncc模版    模板，金字塔等级的最大数量，起始角度，角度步长，模型ID
    CreateNccModel(ho_nccImageReduced, 5, -0.39, 0.79, "auto", "use_polarity", &hv_nccModelID);
    ui->label_creatmsg->setText("已创建模板！");
    statusBar->showMessage("已创建模板！");
    nccmsg = "ok";
    ui->pushButton_nccclear->setEnabled(true);
    ui->pushButton_creatncc->setEnabled(true);
    ui->pushButton_nccimage->setEnabled(true);
    ui->pushButton_findimage->setEnabled(true);
    ui->pushButton_findncc->setEnabled(true);
}

void MainWindow::on_pushButton_findncc_clicked()
{
    double nccjindu = ui->doubleSpinBox_nccjindu->value();
    double nccchongdie = ui->doubleSpinBox_nccchongdie->value();
    QString nccnumber = ui->comboBox_nccnumber->currentText();
    Rgb1ToGray(ho_nccImage, &ho_nccGrayImage1);
    DispObj(ho_nccImage, hv_WindowHandle2);
    //应用模板进行匹配 灰度图像，模型ID，起始角度，角度范围，匹配度，目标个数，最大重叠，子像素精度，金字塔等级数，
    FindNccModel(ho_nccGrayImage1, hv_nccModelID, -0.39, 0.79, nccjindu, nccnumber.toInt(), nccchongdie, "true",
                 5, &hv_nccRow, &hv_nccColumn, &hv_nccAngle, &hv_nccScore);
    GenRectangle1(&ho_nccRectangle1, hv_nccRow-((hv_nccRow2-hv_nccRow1)/2), hv_nccColumn-((hv_nccColumn2-hv_nccColumn1)/2),
                  hv_nccRow+((hv_nccRow2-hv_nccRow1)/2), hv_nccColumn+((hv_nccColumn2-hv_nccColumn1)/2));
    CountObj(ho_nccRectangle1, &hv_nccNumber);  // 计算设别到的个数
    DispObj(ho_nccRectangle1, hv_WindowHandle2);
    QueryFont(hv_WindowHandle2, &hv_Font); // 获取字体尺寸
    hv_FontWithSize = HTuple(hv_Font[0])+"-20"; // 设置显示字体大小，可修改 -20
    SetFont(hv_WindowHandle2, hv_FontWithSize);
    DispText(hv_WindowHandle2,hv_nccScore, "image", hv_nccRow, hv_nccColumn,  // 显示匹配度
             "black", HTuple(), HTuple());
    statusBar->showMessage("完成模板匹配.");
    QString nccnumbermsg = QString::number(hv_nccNumber.D());
    ui->pushButton_nccnumber->setText(nccnumbermsg);
    // 显示数据
    HTuple  hv_i, hv_scorenccmsg, hv_rownccmsg, hv_columnnccmsg;
    HTuple end_val29 = hv_nccNumber;
    HTuple step_val29 = 1;
    for (hv_i=1; hv_i.Continue(end_val29, step_val29); hv_i += step_val29)
    {
        hv_scorenccmsg = HTuple(hv_nccScore[hv_i-1]);  // 获取halcon匹配度 坐标
        hv_rownccmsg = HTuple(hv_nccRow[hv_i-1]);
        hv_columnnccmsg = HTuple(hv_nccColumn[hv_i-1]);
        QString scorenccmsg = QString::number(hv_scorenccmsg.D()); // 转换为qstring
        QString rownccmsg = QString::number(hv_rownccmsg.D());
        QString columnnccmsg = QString::number(hv_columnnccmsg.D());
        QString  ncci= QString::number(hv_i.D());
        ui->textEdit_ncc->append(ncci+":"+scorenccmsg+"("+columnnccmsg+","+rownccmsg+")");
    }
}

void MainWindow::on_pushButton_findimage_clicked()
{
    ReadImage(&ho_nccImage, Pathncc.toStdString().c_str());
    statusBar->showMessage(Pathncc+":图片已载入窗口！");
}

void MainWindow::on_pushButton_nccclearmsg_clicked()
{
    ui->textEdit_ncc->clear();
}

void MainWindow::on_pushButton_fileshape_clicked()
{
    // Pathfileshape = ui->lineEdit_fileshale->text();
    // QMessageBox::information(this,"提示",Pathfileshape);
    Pathfileshape = QFileDialog::getOpenFileName(this,"文件夹：","/");
    ui->lineEdit_fileshale->setText(Pathfileshape);
}

void MainWindow::on_pushButton_imageshape_clicked()
{
    CloseWindow(hv_WindowHandle3); //关闭当前窗口
    winId_shape = (Hlong)this->ui->graphicsView_shape->winId(); //绑定窗口
    ReadImage(&ho_Imageshape, Pathfileshape.toStdString().c_str()); //读取图片
    GetImageSize(ho_Imageshape, &hv_Widthshape, &hv_Heightshape); //获取图片尺寸
    QString imagewshape = QString::number(hv_Widthshape.D());
    QString imagehshape = QString::number(hv_Heightshape.D());
    int wshape = imagewshape.toInt();
    int hshape = imagehshape.toInt();
    shapearea2 = wshape*hshape;
    ui->horizontalSlider_choiceshape3->setRange(0, shapearea2);
    ui->horizontalSlider_choiceshape4->setRange(0, shapearea2);
    ui->horizontalSlider_choiceshape4->setValue(shapearea2);     // 设置初始值为255
    OpenWindow(0,0,ui->graphicsView_shape->width(),ui->graphicsView_shape->height(),winId_shape,"visible","",&hv_WindowHandle3); // 打开窗口
    SetWindowAttr("background_color","black"); // 设置背景颜色
    SetLineWidth(hv_WindowHandle3,5);
    SetPart(hv_WindowHandle3,0, 0, hv_Heightshape - 1, hv_Widthshape - 1); //设置图像显示为充满图像
    DispObj(ho_Imageshape, hv_WindowHandle3); // 显示图片
    statusBar->showMessage(Pathfileshape+":图片已载入窗口！");
    ui->pushButton_clearshape->setEnabled(true);
    ui->pushButton_choiceshape->setEnabled(true);
}

void MainWindow::on_pushButton_clearshape_clicked()
{
    if(shapemsg == "ok"){
        ClearShapeModel(hv_ModelIDshape);
        ui->label_createshapemsg->setText("无形状！");
        shapemsg = "no";
    }
    CloseWindow(hv_WindowHandle3);
    statusBar->showMessage("窗口已清理！");
    s = "no";
    ui->pushButton_clearshape->setEnabled(false);
    ui->horizontalSlider_choiceshape1->setEnabled(false);
    ui->horizontalSlider_choiceshape2->setEnabled(false);
    ui->horizontalSlider_choiceshape3->setEnabled(false);
    ui->horizontalSlider_choiceshape4->setEnabled(false);
    ui->pushButton_choiceshape->setEnabled(false);
    ui->pushButton_choiceshape1->setEnabled(false);
    ui->pushButton_createshape->setEnabled(false);
    ui->pushButton_18->setEnabled(false);
    ui->pushButton_11->setEnabled(false);
    ui->pushButton_shapefind->setEnabled(false);
}

void MainWindow::on_pushButton_choiceshape_clicked()
{
    s = "ok";
    ui->horizontalSlider_choiceshape1->setEnabled(true);
    ui->horizontalSlider_choiceshape2->setEnabled(true);
    ui->pushButton_11->setEnabled(true);
    statusBar->showMessage("通过灰度阈值和面积进行选择!");
}

void MainWindow::on_horizontalSlider_choiceshape1_valueChanged(int valuechoiceshape1)
{
    shape1 = valuechoiceshape1;
    shape_msg1 = QString("%1").arg(valuechoiceshape1);
    ui->label_shape1->setText(shape_msg1);
    if( shape1 < shape2){  // 判断是否有交叉
        if(s == "ok"){
            Rgb1ToGray(ho_Imageshape, &ho_GrayImageshape);
            SetColor(hv_WindowHandle3,"red");
            Threshold(ho_GrayImageshape, &ho_Regionshape, shape1, shape2); //阈值分割
            Connection(ho_Regionshape, &ho_ConnectedRegionsshape); //连接区域
            CountObj(ho_ConnectedRegionsshape, &hv_Numbershape); //数目
            QString snamber = QString::number(hv_Numbershape.D());
            ui->label_shapenumber->setText(snamber);
            ClearWindow(hv_WindowHandle3);
            DispObj(ho_Regionshape, hv_WindowHandle3);
            statusBar->showMessage("红色为被选区域！");
        }
    }else{
        shape2 = shape1 + 1;
        ui->horizontalSlider_choiceshape2->setValue(shape2);
    }
}

void MainWindow::on_horizontalSlider_choiceshape2_valueChanged(int valuechoiceshape2)
{
    shape2 = valuechoiceshape2;
    shape_msg2 = QString("%1").arg(valuechoiceshape2);
    ui->label_shape2->setText(shape_msg2);
    if( shape1 < shape2){
        if(s == "ok"){
            Rgb1ToGray(ho_Imageshape, &ho_GrayImageshape);
            SetColor(hv_WindowHandle3,"red");
            Threshold(ho_GrayImageshape, &ho_Regionshape, shape1, shape2);
            Connection(ho_Regionshape, &ho_ConnectedRegionsshape);
            CountObj(ho_ConnectedRegionsshape, &hv_Numbershape);
            QString snamber = QString::number(hv_Numbershape.D());
            ui->label_shapenumber->setText(snamber);
            ClearWindow(hv_WindowHandle3);
            DispObj(ho_Regionshape, hv_WindowHandle3);
            statusBar->showMessage("红色为被选区域！");
        }
    }else{
        shape1 = shape2 - 1;
        ui->horizontalSlider_choiceshape1->setValue(shape1);
    }
}

void MainWindow::on_pushButton_choiceshape1_clicked()
{
    s = "no";
    ui->pushButton_choiceshape1->setEnabled(false);
    ui->horizontalSlider_choiceshape1->setEnabled(false);
    ui->horizontalSlider_choiceshape2->setEnabled(false);
    ui->horizontalSlider_choiceshape3->setEnabled(false);
    ui->horizontalSlider_choiceshape4->setEnabled(false);
    ui->pushButton_createshape->setEnabled(true);
    statusBar->showMessage("形状已选！");
}

void MainWindow::on_horizontalSlider_choiceshape3_valueChanged(int valuechoiceshape3)
{
    shapearea1 = valuechoiceshape3;
    ui->label_shapearea1->setText(QString("%1").arg(valuechoiceshape3));
    if( shapearea1 < shapearea2){  // 判断是否有交叉
        if(s == "ok"){
            SetColor(hv_WindowHandle3,"red");
            SelectShape(ho_ConnectedRegionsshape, &ho_SelectedRegionsshape, "area", "and", shapearea1, shapearea2); //挑选
            CountObj(ho_SelectedRegionsshape, &hv_Numbershape); //区域个数
            QString snamber = QString::number(hv_Numbershape.D());
            ui->label_shapenumber->setText(snamber);
            FillUp(ho_SelectedRegionsshape, &ho_RegionFillUpshape); //填充
            DilationCircle(ho_RegionFillUpshape, &ho_RegionDilationshape, 5.5); //膨胀
            ReduceDomain(ho_GrayImageshape, ho_RegionDilationshape, &ho_ImageReducedshape); //抠图
            ClearWindow(hv_WindowHandle3);
            DispObj(ho_SelectedRegionsshape, hv_WindowHandle3);
            statusBar->showMessage("红色为被选区域！");
        }
    }else{
        shapearea2 = shapearea1 + 1;
        ui->horizontalSlider_choiceshape4->setValue(shapearea2);
    }
}

void MainWindow::on_horizontalSlider_choiceshape4_valueChanged(int valuechoiceshape4)
{
    shapearea2 = valuechoiceshape4;
    ui->label_shapearea2->setText(QString("%1").arg(valuechoiceshape4));
    if( shapearea1 < shapearea2){
        if(s == "ok"){
            SetColor(hv_WindowHandle3,"red");
            SelectShape(ho_ConnectedRegionsshape, &ho_SelectedRegionsshape, "area", "and", shapearea1, shapearea2);
            CountObj(ho_SelectedRegionsshape, &hv_Numbershape);
            QString snamber = QString::number(hv_Numbershape.D());
            ui->label_shapenumber->setText(snamber);
            FillUp(ho_SelectedRegionsshape, &ho_RegionFillUpshape);
            DilationCircle(ho_RegionFillUpshape, &ho_RegionDilationshape, 5.5);
            ReduceDomain(ho_GrayImageshape, ho_RegionDilationshape, &ho_ImageReducedshape);
            ClearWindow(hv_WindowHandle3);
            DispObj(ho_SelectedRegionsshape, hv_WindowHandle3);
            statusBar->showMessage("红色为被选区域！");
        }
    }else{
        shapearea1 = shapearea2 - 1;
        ui->horizontalSlider_choiceshape3->setValue(shapearea1);
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    ui->pushButton_11->setEnabled(false);
    ui->horizontalSlider_choiceshape1->setEnabled(false);
    ui->horizontalSlider_choiceshape2->setEnabled(false);
    ui->horizontalSlider_choiceshape3->setEnabled(true);
    ui->horizontalSlider_choiceshape4->setEnabled(true);
    ui->pushButton_choiceshape1->setEnabled(true);
    statusBar->showMessage("灰度阈值已确定!");
}

void MainWindow::on_pushButton_createshape_clicked()
{
    //创建模版   模板 金字塔 图案的最小旋转 旋转角度的大小 步长 图案最小比例 图案的最大比例 缩放步长（分辨率）
    CreateScaledShapeModel(ho_ImageReducedshape, 5, HTuple(-180).TupleRad(), HTuple(180).TupleRad(),
                           "auto", ui->doubleSpinBox_shapemin->value(), ui->doubleSpinBox_shapemax->value(),
                           "auto", "none", "ignore_global_polarity", 40, 10, &hv_ModelIDshape);
    GetShapeModelContours(&ho_ModelContoursshape, hv_ModelIDshape, 1); //获取模版轮廓
    AreaCenter(ho_RegionFillUpshape, &hv_Areashape, &hv_Rowshape, &hv_Columnshape); //显示模版轮廓到模版位置
    VectorAngleToRigid(0, 0, 0, hv_Rowshape, hv_Rowshape, 0, &hv_HomMat2Dshape); //仿射变换
    AffineTransContourXld(ho_ModelContoursshape, &ho_ContoursAffineTransshape, hv_HomMat2Dshape); //应用任意仿射二维变换到XLD轮廓。
    DispObj(ho_Imageshape, hv_WindowHandle3);
    DispObj(ho_ContoursAffineTransshape, hv_WindowHandle3);
    shapemsg = "ok";
    ui->label_createshapemsg->setText("已创建！");
    statusBar->showMessage("形状模型已创建！");
    ui->pushButton_18->setEnabled(true);
    ui->pushButton_createshape->setEnabled(false);
}

void MainWindow::on_pushButton_18_clicked()
{
    CloseWindow(hv_WindowHandle3);
    ReadImage(&ho_Imageshape, Pathfileshape.toStdString().c_str());
    GetImageSize(ho_Imageshape, &hv_Widthshape, &hv_Heightshape);
    OpenWindow(0,0,ui->graphicsView_shape->width(),ui->graphicsView_shape->height(),winId_shape,"visible","",&hv_WindowHandle3);
    SetPart(hv_WindowHandle3,0, 0, hv_Heightshape - 1, hv_Widthshape - 1);
    DispObj(ho_Imageshape, hv_WindowHandle3); // 显示图片
    statusBar->showMessage(Pathfileshape+":图片已载入窗口，可配置参数进行识别！");
    ui->pushButton_shapefind->setEnabled(true);
}

void MainWindow::on_pushButton_shapefind_clicked()
{
    Rgb1ToGray(ho_Imageshape, &ho_GrayImageshape);
    //匹配模版
    FindScaledShapeModel(ho_GrayImageshape, hv_ModelIDshape, HTuple(-180).TupleRad(),
                         HTuple(180).TupleRad(), ui->doubleSpinBox_shapemin->value(), ui->doubleSpinBox_shapemax->value(),
                         ui->doubleSpinBox_shapejindu->value(), ui->comboBox_shapenb->currentText().toInt(), ui->doubleSpinBox_shapechongdie->value(),
                         "least_squares", 5, 0.5, &hv_Rowshape1,
                         &hv_Columnshape1, &hv_Angleshape, &hv_Scalesahpe, &hv_Scoreshape);
    HTuple end_val43 = (hv_Scoreshape.TupleLength())-1;
    HTuple step_val43 = 1;
    for (hv_i=0; hv_i.Continue(end_val43, step_val43); hv_i += step_val43)
    {
        HomMat2dIdentity(&hv_HomMat2DIdentityshape); //生成相同二维变换的齐次变换矩阵。
        HomMat2dTranslate(hv_HomMat2DIdentityshape, HTuple(hv_Rowshape1[hv_i]), HTuple(hv_Columnshape1[hv_i]),  //向齐次二维变换矩阵添加一个平移。
                          &hv_HomMat2DTranslateshape);
        HomMat2dRotate(hv_HomMat2DTranslateshape, HTuple(hv_Angleshape[hv_i]), HTuple(hv_Rowshape1[hv_i]), //添加一个旋转到齐次二维变换矩阵。
                       HTuple(hv_Columnshape1[hv_i]), &hv_HomMat2DRotateshape);
        HomMat2dScale(hv_HomMat2DRotateshape, HTuple(hv_Scalesahpe[hv_i]), HTuple(hv_Scalesahpe[hv_i]),  //向齐次二维变换矩阵添加缩放。
                      HTuple(hv_Rowshape1[hv_i]), HTuple(hv_Columnshape1[hv_i]), &hv_HomMat2DScaleshape);
        AffineTransContourXld(ho_ModelContoursshape, &ho_ContoursAffineTransshape, hv_HomMat2DScaleshape);  //应用任意仿射二维变换到XLD轮廓。
        SetColor(hv_WindowHandle3,"red");
        SetLineWidth(hv_WindowHandle3,5);
        DispObj(ho_ContoursAffineTransshape, hv_WindowHandle3);
        ui->textEdit_shape->append(QString::number((hv_i+1).D())+". ("+QString::number(HTuple(hv_Columnshape1[hv_i]).D())+", "
                                   +QString::number(HTuple(hv_Rowshape1[hv_i]).D())+")"+" 比例:"
                                   +QString::number(HTuple(hv_Scalesahpe[hv_i]).D())+" 相似度："
                                   +QString::number(HTuple(hv_Scoreshape[hv_i]).D()));  //对话框输出
    }
    QString shapenumber = QString::number(hv_Scoreshape.TupleLength().D());
    ui->pushButton_shapefindnb->setText(shapenumber);
    statusBar->showMessage("已识别，信息已输出！");
}

void MainWindow::on_pushButton_shapemsgclear_clicked()
{
    ui->textEdit_shape->clear();
    statusBar->showMessage("信息已清除！");
}

