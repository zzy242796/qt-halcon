#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <Halcon.h>
#include "HalconCpp.h"
#include <HDevThread.h>
using namespace HalconCpp;

#include <QMainWindow>
#include <QStatusBar>
#include <QString>
#include <QTimer>
#include <QSize>
#include <QTcpServer>
#include <QTcpSocket>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QTcpServer* server;

    //camera
    HObject  ho_image,ho_image1,ho_camera,ho_Regions,ho_ImageEmphasize,ho_GrayImage;
    HTuple  hv_Width, hv_Height, hv_WindowHandle,hv_AcqHandle;
    HTuple  hv_Width1, hv_Height1,hv_Widthncc,hv_Heightncc;
    HTuple hv_WindowHandle1;
    Hlong winId,winId_image,winId_ncc,winId_shape,winId_color;
    //image
    HObject  ho_Circle, ho_RegionLines,ho_ImageScaled;
    HObject  ho_Ellipse, ho_Rectangle, ho_Rectangle1, ho_PolygonRegion;
    HTuple  hv_Row, hv_Column, hv_Radius;
    HTuple  hv_Row1, hv_Column1, hv_Row2, hv_Column2, hv_Row3;
    HTuple  hv_Column3, hv_Phi, hv_Radius1, hv_Radius2, hv_Row11;
    HTuple  hv_Column11, hv_Row21, hv_Column21, hv_Row4, hv_Column4;
    HTuple  hv_Phi1, hv_Length1, hv_Length2;
    //ncc
    HObject  ho_nccImage, ho_nccGrayImage, ho_nccRectangle;
    HObject  ho_nccImageReduced, ho_nccGrayImage1, ho_nccRectangle1;
    HObject  ho_nccRegionSelected;
    HTuple  hv_WindowHandle2, hv_nccRow1, hv_nccColumn1;
    HTuple  hv_nccRow2, hv_nccColumn2, hv_nccModelID, hv_nccRow;
    HTuple  hv_nccColumn, hv_nccAngle, hv_nccScore, hv_nccNumber;
    HTuple  hv_Font, hv_FontWithSize;
    //shape
    HObject  ho_Imageshape, ho_GrayImageshape, ho_Regionshape;
    HObject  ho_ConnectedRegionsshape, ho_SelectedRegionsshape;
    HObject  ho_RegionFillUpshape, ho_RegionDilationshape, ho_ImageReducedshape;
    HObject  ho_ModelContoursshape, ho_ContoursAffineTransshape;
    HTuple  hv_Widthshape, hv_Heightshape, hv_WindowHandle3;
    HTuple  hv_Numbershape, hv_ModelIDshape, hv_Areashape, hv_Rowshape;
    HTuple  hv_Columnshape, hv_HomMat2Dshape;
    HTuple  hv_Rowshape1, hv_Columnshape1, hv_Angleshape, hv_Scalesahpe;
    HTuple  hv_Scoreshape, hv_i, hv_HomMat2DIdentityshape, hv_HomMat2DTranslateshape;
    HTuple  hv_HomMat2DRotateshape, hv_HomMat2DScaleshape;
    //color
    HObject  ho_Imagecolor, ho_ImageMeancolor, ho_Redcolor;
    HObject  ho_Greencolor, ho_Bluecolor, ho_Huecolor, ho_Saturationcolor;
    HObject  ho_Intensitycolor, ho_HighSaturationcolor, ho_HueHighSaturationcolor;
    HObject  ho_greencolor, ho_ConnectedRegionscolor, ho_SelectedRegionscolor;
    HObject  ho_Rectanglecolor;
    HTuple  hv_WindowHandle4, hv_Rowcolor, hv_Columncolor,hv_Widthcolor, hv_Heightcolor;
    HTuple  hv_Phicolor, hv_Lengthcolor1, hv_Lengthcolor2, hv_Numbercolor;


private slots:

    void on_pushButton_image_file_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_0_video_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_stop_clicked();
    void camera();
    void closeEvent(QCloseEvent *event) override;
    void on_pushButton_clear_clicked();
    void on_pushButton_gray_clicked();
    void on_pushButton_save_clicked();
    void on_horizontalSlider_Threshold1_valueChanged(int value1);
    void on_horizontalSlider_Threshold2_valueChanged(int value2);
    void on_pushButton_Threshold1_clicked();
    void on_pushButton_emphasize1_clicked();
    void on_pushButton_emphasize2_clicked();
    void on_pushButton_drawcircle_clicked();
    void on_pushButton_line_clicked();
    void on_pushButton_Rectangle1_clicked();
    void on_pushButton_Rectangle2_clicked();
    void on_pushButton_Ellipse_clicked();
    void on_pushButton_Polygon_clicked();
    void on_pushButton_scale_clicked();
    void on_horizontalSlider_scale1_valueChanged(int value3);
    void on_doubleSpinBox_scale_valueChanged(double arg1);
    void on_pushButton_Threshold2_clicked();
    void on_pushButton_draw_clicked();
    void on_doubleSpinBox_emphasize_valueChanged(double arg2);
    void on_comboBox_emphasize_currentTextChanged(const QString &arg3);
    void on_pushButton_scale1_clicked();
    void on_pushButton_nccfile_clicked();
    void on_pushButton_nccimage_clicked();
    void on_pushButton_nccclear_clicked();
    void on_pushButton_creatncc_clicked();
    void on_pushButton_findncc_clicked();
    void on_pushButton_findimage_clicked();
    void on_pushButton_nccclearmsg_clicked();
    void on_pushButton_fileshape_clicked();
    void on_pushButton_imageshape_clicked();
    void on_pushButton_clearshape_clicked();
    void on_pushButton_choiceshape_clicked();
    void on_horizontalSlider_choiceshape1_valueChanged(int valuechoiceshape1);
    void on_horizontalSlider_choiceshape2_valueChanged(int valuechoiceshape2);
    void on_pushButton_choiceshape1_clicked();
    void on_horizontalSlider_choiceshape3_valueChanged(int valuechoiceshape3);
    void on_horizontalSlider_choiceshape4_valueChanged(int valuechoiceshape4);
    void on_pushButton_11_clicked();
    void on_pushButton_createshape_clicked();
    void on_pushButton_18_clicked();
    void on_pushButton_shapefind_clicked();
    void on_pushButton_shapemsgclear_clicked();
    void on_pushButton_colorfile_clicked();
    void on_pushButton_clearcolor_clicked();
    void on_pushButton_findred_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_findcamera_clicked();
    void on_pushButton_tcpstart_clicked();
    void on_pushButton_tcpout_clicked();
    void on_pushButton_tcpsend_clicked();
    void on_pushButton_newnumber_clicked();
    void on_pushButton_clientconnect_clicked();
    void on_pushButton_clientsend_clicked();
    void on_pushButton_clientout_clicked();


private:
    Ui::MainWindow *ui;
    QTcpSocket* client_tcp;

    QTimer * timer;
    QString camera_video,tcpstart;
    QString Path,Pathncc,Pathfileshape;
    QString stop_msg,nccmsg,shapemsg;
    QString image_style,image_field;
    QStatusBar *statusBar;
    QString Threshold_msg1,Threshold_msg2,t,s,Threshold_color,draw_color,shape_msg1,shape_msg2;
    int Threshold1,Threshold2,scale1,shape1,shape2,shapearea1,shapearea2,colorbuild1,colorbuild2;
    QString emphasize_msg2,scale_msg,emphasize1;
    double emphasize_msg1,scale2;
};
#endif // MAINWINDOW_H
