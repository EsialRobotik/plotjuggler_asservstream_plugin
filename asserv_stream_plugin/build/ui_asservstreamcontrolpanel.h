/********************************************************************************
** Form generated from reading UI file 'asservstreamcontrolpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASSERVSTREAMCONTROLPANEL_H
#define UI_ASSERVSTREAMCONTROLPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AsservStreamControlPanel
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QTabWidget *tabWidget;
    QWidget *tab_vitesse_gauche;
    QPushButton *vitesse_gauche_update_btn;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *vitesse_gauche_Kp;
    QDoubleSpinBox *vitesse_gauche_Ki;
    QLabel *label_4;
    QSpinBox *vitesse_gauche_range;
    QLabel *vitesse_gauche_range_lb;
    QWidget *tab_vitesse_droite;
    QLabel *label_22;
    QLabel *label_23;
    QPushButton *vitesse_droite_update_btn;
    QDoubleSpinBox *vitesse_droite_Ki;
    QDoubleSpinBox *vitesse_droite_Kp;
    QLabel *label_24;
    QSpinBox *vitesse_droite_range;
    QLabel *vitesse_droite_range_lb;
    QWidget *tab_distance;
    QDoubleSpinBox *distance_Kp;
    QLabel *label_5;
    QPushButton *distance_update_btn;
    QWidget *tab_angle;
    QDoubleSpinBox *angle_Kp;
    QLabel *label_25;
    QPushButton *angle_update_btn;
    QWidget *tab_acc_angle;
    QPushButton *angle_acc_update_btn;
    QLabel *label_29;
    QDoubleSpinBox *angle_acc;
    QLabel *label_32;
    QLabel *label_34;
    QWidget *tab_acc_dist;
    QLabel *label_33;
    QLabel *label_30;
    QDoubleSpinBox *dist_acc_max;
    QPushButton *distance_acc_update_btn;
    QLabel *label_31;
    QDoubleSpinBox *dist_acc_min;
    QLabel *label_49;
    QLabel *label_50;
    QDoubleSpinBox *dist_acc_threshold;
    QLabel *label_51;
    QLabel *label_52;
    QGroupBox *group_motor_control;
    QPushButton *motor_enable_btn;
    QPushButton *motor_disable_btn;
    QGroupBox *groupBox_3;
    QLabel *label_6;
    QDoubleSpinBox *pos_cmd;
    QPushButton *pos_cmd_btn;
    QFrame *line;
    QLabel *label_7;
    QDoubleSpinBox *robot_speed_lin_cmd;
    QFrame *line_2;
    QPushButton *robot_speed_lin_cmd_btn;
    QLabel *label_10;
    QLabel *label_12;
    QFrame *line_3;
    QLabel *label_11;
    QDoubleSpinBox *angle_cmd;
    QLabel *label_8;
    QPushButton *angle_cmd_btn;
    QLabel *label_13;
    QLabel *label_9;
    QDoubleSpinBox *robot_speed_ang_cmd;
    QPushButton *robot_speed_ang_cmd_btn;
    QFrame *line_4;
    QPushButton *left_whell_speed_cmd_btn;
    QDoubleSpinBox *left_wheel_speed_cmd;
    QLabel *label_14;
    QLabel *label_15;
    QFrame *line_5;
    QDoubleSpinBox *right_wheel_speed_cmd;
    QLabel *label_16;
    QPushButton *right_whell_speed_cmd_btn;
    QLabel *label_17;
    QFrame *line_6;
    QFrame *line_7;
    QLabel *label_26;
    QSpinBox *speed_consign_duration;
    QLabel *label_27;
    QFrame *line_8;
    QLabel *label_18;
    QSpinBox *goto_X;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QSpinBox *goto_Y;
    QLabel *label_28;
    QPushButton *goto_cmd_btn;
    QGroupBox *dist_angle_controlmotor_control_2;
    QPushButton *distAngle_enable_btn;
    QPushButton *distAngle_disable_btn;
    QGroupBox *group_reset;
    QPushButton *reset_btn;
    QGroupBox *group_get_config;
    QPushButton *get_config_btn;
    QPushButton *update_config_btn;
    QGroupBox *group_reset_2;
    QPushButton *goto_test_btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AsservStreamControlPanel)
    {
        if (AsservStreamControlPanel->objectName().isEmpty())
            AsservStreamControlPanel->setObjectName(QStringLiteral("AsservStreamControlPanel"));
        AsservStreamControlPanel->resize(1194, 943);
        centralWidget = new QWidget(AsservStreamControlPanel);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 30, 811, 271));
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        groupBox->setFlat(false);
        groupBox->setCheckable(false);
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(20, 20, 781, 241));
        tab_vitesse_gauche = new QWidget();
        tab_vitesse_gauche->setObjectName(QStringLiteral("tab_vitesse_gauche"));
        vitesse_gauche_update_btn = new QPushButton(tab_vitesse_gauche);
        vitesse_gauche_update_btn->setObjectName(QStringLiteral("vitesse_gauche_update_btn"));
        vitesse_gauche_update_btn->setGeometry(QRect(400, 60, 99, 27));
        label_2 = new QLabel(tab_vitesse_gauche);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 121, 31));
        label_3 = new QLabel(tab_vitesse_gauche);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 110, 121, 31));
        vitesse_gauche_Kp = new QDoubleSpinBox(tab_vitesse_gauche);
        vitesse_gauche_Kp->setObjectName(QStringLiteral("vitesse_gauche_Kp"));
        vitesse_gauche_Kp->setGeometry(QRect(120, 70, 91, 27));
        vitesse_gauche_Kp->setDecimals(4);
        vitesse_gauche_Kp->setSingleStep(0.1);
        vitesse_gauche_Ki = new QDoubleSpinBox(tab_vitesse_gauche);
        vitesse_gauche_Ki->setObjectName(QStringLiteral("vitesse_gauche_Ki"));
        vitesse_gauche_Ki->setGeometry(QRect(120, 110, 91, 27));
        vitesse_gauche_Ki->setDecimals(4);
        vitesse_gauche_Ki->setSingleStep(0.1);
        label_4 = new QLabel(tab_vitesse_gauche);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 30, 101, 21));
        vitesse_gauche_range = new QSpinBox(tab_vitesse_gauche);
        vitesse_gauche_range->setObjectName(QStringLiteral("vitesse_gauche_range"));
        vitesse_gauche_range->setEnabled(true);
        vitesse_gauche_range->setGeometry(QRect(120, 30, 48, 27));
        vitesse_gauche_range->setMaximum(2);
        vitesse_gauche_range_lb = new QLabel(tab_vitesse_gauche);
        vitesse_gauche_range_lb->setObjectName(QStringLiteral("vitesse_gauche_range_lb"));
        vitesse_gauche_range_lb->setGeometry(QRect(20, 140, 481, 61));
        vitesse_gauche_range_lb->setWordWrap(true);
        tabWidget->addTab(tab_vitesse_gauche, QString());
        tab_vitesse_droite = new QWidget();
        tab_vitesse_droite->setObjectName(QStringLiteral("tab_vitesse_droite"));
        label_22 = new QLabel(tab_vitesse_droite);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(10, 30, 101, 21));
        label_23 = new QLabel(tab_vitesse_droite);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(10, 110, 121, 31));
        vitesse_droite_update_btn = new QPushButton(tab_vitesse_droite);
        vitesse_droite_update_btn->setObjectName(QStringLiteral("vitesse_droite_update_btn"));
        vitesse_droite_update_btn->setGeometry(QRect(400, 60, 99, 27));
        vitesse_droite_Ki = new QDoubleSpinBox(tab_vitesse_droite);
        vitesse_droite_Ki->setObjectName(QStringLiteral("vitesse_droite_Ki"));
        vitesse_droite_Ki->setGeometry(QRect(120, 110, 91, 27));
        vitesse_droite_Ki->setDecimals(4);
        vitesse_droite_Ki->setSingleStep(0.1);
        vitesse_droite_Kp = new QDoubleSpinBox(tab_vitesse_droite);
        vitesse_droite_Kp->setObjectName(QStringLiteral("vitesse_droite_Kp"));
        vitesse_droite_Kp->setGeometry(QRect(120, 70, 91, 27));
        vitesse_droite_Kp->setDecimals(4);
        vitesse_droite_Kp->setSingleStep(0.1);
        label_24 = new QLabel(tab_vitesse_droite);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(10, 70, 121, 31));
        vitesse_droite_range = new QSpinBox(tab_vitesse_droite);
        vitesse_droite_range->setObjectName(QStringLiteral("vitesse_droite_range"));
        vitesse_droite_range->setEnabled(true);
        vitesse_droite_range->setGeometry(QRect(120, 30, 48, 27));
        vitesse_droite_range->setMaximum(2);
        vitesse_droite_range_lb = new QLabel(tab_vitesse_droite);
        vitesse_droite_range_lb->setObjectName(QStringLiteral("vitesse_droite_range_lb"));
        vitesse_droite_range_lb->setGeometry(QRect(20, 140, 481, 61));
        vitesse_droite_range_lb->setWordWrap(true);
        tabWidget->addTab(tab_vitesse_droite, QString());
        tab_distance = new QWidget();
        tab_distance->setObjectName(QStringLiteral("tab_distance"));
        distance_Kp = new QDoubleSpinBox(tab_distance);
        distance_Kp->setObjectName(QStringLiteral("distance_Kp"));
        distance_Kp->setGeometry(QRect(120, 50, 91, 27));
        distance_Kp->setDecimals(2);
        distance_Kp->setMaximum(10001);
        distance_Kp->setSingleStep(0.1);
        label_5 = new QLabel(tab_distance);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 40, 121, 51));
        label_5->setWordWrap(true);
        distance_update_btn = new QPushButton(tab_distance);
        distance_update_btn->setObjectName(QStringLiteral("distance_update_btn"));
        distance_update_btn->setGeometry(QRect(400, 60, 99, 27));
        tabWidget->addTab(tab_distance, QString());
        tab_angle = new QWidget();
        tab_angle->setObjectName(QStringLiteral("tab_angle"));
        angle_Kp = new QDoubleSpinBox(tab_angle);
        angle_Kp->setObjectName(QStringLiteral("angle_Kp"));
        angle_Kp->setGeometry(QRect(120, 50, 91, 27));
        angle_Kp->setDecimals(2);
        angle_Kp->setMaximum(10000);
        angle_Kp->setSingleStep(0.1);
        label_25 = new QLabel(tab_angle);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(10, 40, 121, 41));
        angle_update_btn = new QPushButton(tab_angle);
        angle_update_btn->setObjectName(QStringLiteral("angle_update_btn"));
        angle_update_btn->setGeometry(QRect(390, 60, 99, 27));
        tabWidget->addTab(tab_angle, QString());
        tab_acc_angle = new QWidget();
        tab_acc_angle->setObjectName(QStringLiteral("tab_acc_angle"));
        angle_acc_update_btn = new QPushButton(tab_acc_angle);
        angle_acc_update_btn->setObjectName(QStringLiteral("angle_acc_update_btn"));
        angle_acc_update_btn->setGeometry(QRect(390, 60, 99, 27));
        label_29 = new QLabel(tab_acc_angle);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(10, 20, 161, 61));
        label_29->setWordWrap(true);
        angle_acc = new QDoubleSpinBox(tab_acc_angle);
        angle_acc->setObjectName(QStringLiteral("angle_acc"));
        angle_acc->setGeometry(QRect(170, 40, 91, 27));
        angle_acc->setDecimals(1);
        angle_acc->setMaximum(10000);
        angle_acc->setSingleStep(0.1);
        label_32 = new QLabel(tab_acc_angle);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(270, 40, 121, 21));
        label_34 = new QLabel(tab_acc_angle);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(10, 90, 481, 81));
        label_34->setWordWrap(true);
        tabWidget->addTab(tab_acc_angle, QString());
        tab_acc_dist = new QWidget();
        tab_acc_dist->setObjectName(QStringLiteral("tab_acc_dist"));
        label_33 = new QLabel(tab_acc_dist);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(330, 20, 121, 21));
        label_30 = new QLabel(tab_acc_dist);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(10, 0, 211, 61));
        label_30->setWordWrap(true);
        dist_acc_max = new QDoubleSpinBox(tab_acc_dist);
        dist_acc_max->setObjectName(QStringLiteral("dist_acc_max"));
        dist_acc_max->setGeometry(QRect(230, 20, 81, 27));
        dist_acc_max->setDecimals(1);
        dist_acc_max->setMaximum(10000);
        dist_acc_max->setSingleStep(0.1);
        distance_acc_update_btn = new QPushButton(tab_acc_dist);
        distance_acc_update_btn->setObjectName(QStringLiteral("distance_acc_update_btn"));
        distance_acc_update_btn->setGeometry(QRect(390, 60, 99, 27));
        label_31 = new QLabel(tab_acc_dist);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(10, 50, 361, 61));
        label_31->setWordWrap(true);
        dist_acc_min = new QDoubleSpinBox(tab_acc_dist);
        dist_acc_min->setObjectName(QStringLiteral("dist_acc_min"));
        dist_acc_min->setGeometry(QRect(230, 120, 81, 27));
        dist_acc_min->setDecimals(1);
        dist_acc_min->setMaximum(10000);
        dist_acc_min->setSingleStep(0.1);
        label_49 = new QLabel(tab_acc_dist);
        label_49->setObjectName(QStringLiteral("label_49"));
        label_49->setGeometry(QRect(330, 120, 121, 21));
        label_50 = new QLabel(tab_acc_dist);
        label_50->setObjectName(QStringLiteral("label_50"));
        label_50->setGeometry(QRect(10, 100, 221, 61));
        label_50->setWordWrap(true);
        dist_acc_threshold = new QDoubleSpinBox(tab_acc_dist);
        dist_acc_threshold->setObjectName(QStringLiteral("dist_acc_threshold"));
        dist_acc_threshold->setGeometry(QRect(230, 160, 81, 27));
        dist_acc_threshold->setDecimals(1);
        dist_acc_threshold->setMaximum(10000);
        dist_acc_threshold->setSingleStep(0.1);
        label_51 = new QLabel(tab_acc_dist);
        label_51->setObjectName(QStringLiteral("label_51"));
        label_51->setGeometry(QRect(330, 160, 121, 21));
        label_52 = new QLabel(tab_acc_dist);
        label_52->setObjectName(QStringLiteral("label_52"));
        label_52->setGeometry(QRect(10, 150, 211, 41));
        label_52->setWordWrap(true);
        tabWidget->addTab(tab_acc_dist, QString());
        group_motor_control = new QGroupBox(centralWidget);
        group_motor_control->setObjectName(QStringLiteral("group_motor_control"));
        group_motor_control->setGeometry(QRect(890, 190, 171, 101));
        group_motor_control->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        group_motor_control->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        group_motor_control->setFlat(true);
        motor_enable_btn = new QPushButton(group_motor_control);
        motor_enable_btn->setObjectName(QStringLiteral("motor_enable_btn"));
        motor_enable_btn->setGeometry(QRect(30, 20, 99, 27));
        motor_disable_btn = new QPushButton(group_motor_control);
        motor_disable_btn->setObjectName(QStringLiteral("motor_disable_btn"));
        motor_disable_btn->setGeometry(QRect(30, 60, 99, 27));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(30, 330, 851, 421));
        groupBox_3->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 270, 221, 31));
        label_6->setWordWrap(true);
        pos_cmd = new QDoubleSpinBox(groupBox_3);
        pos_cmd->setObjectName(QStringLiteral("pos_cmd"));
        pos_cmd->setGeometry(QRect(238, 270, 81, 27));
        pos_cmd->setDecimals(0);
        pos_cmd->setMinimum(-3000);
        pos_cmd->setMaximum(3000);
        pos_cmd->setValue(100);
        pos_cmd_btn = new QPushButton(groupBox_3);
        pos_cmd_btn->setObjectName(QStringLiteral("pos_cmd_btn"));
        pos_cmd_btn->setGeometry(QRect(530, 270, 251, 27));
        line = new QFrame(groupBox_3);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 180, 371, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 190, 261, 61));
        label_7->setWordWrap(true);
        robot_speed_lin_cmd = new QDoubleSpinBox(groupBox_3);
        robot_speed_lin_cmd->setObjectName(QStringLiteral("robot_speed_lin_cmd"));
        robot_speed_lin_cmd->setGeometry(QRect(272, 210, 81, 27));
        robot_speed_lin_cmd->setDecimals(0);
        robot_speed_lin_cmd->setMinimum(-3000);
        robot_speed_lin_cmd->setMaximum(3000);
        line_2 = new QFrame(groupBox_3);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setEnabled(true);
        line_2->setGeometry(QRect(10, 250, 761, 20));
        line_2->setLineWidth(2);
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        robot_speed_lin_cmd_btn = new QPushButton(groupBox_3);
        robot_speed_lin_cmd_btn->setObjectName(QStringLiteral("robot_speed_lin_cmd_btn"));
        robot_speed_lin_cmd_btn->setGeometry(QRect(580, 200, 251, 27));
        label_10 = new QLabel(groupBox_3);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(330, 270, 67, 21));
        label_12 = new QLabel(groupBox_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(352, 190, 61, 61));
        line_3 = new QFrame(groupBox_3);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setGeometry(QRect(10, 300, 701, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        label_11 = new QLabel(groupBox_3);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(330, 320, 67, 21));
        angle_cmd = new QDoubleSpinBox(groupBox_3);
        angle_cmd->setObjectName(QStringLiteral("angle_cmd"));
        angle_cmd->setGeometry(QRect(238, 320, 81, 27));
        angle_cmd->setMinimum(-100);
        angle_cmd->setMaximum(100);
        angle_cmd->setValue(3.14);
        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 320, 221, 31));
        label_8->setWordWrap(true);
        angle_cmd_btn = new QPushButton(groupBox_3);
        angle_cmd_btn->setObjectName(QStringLiteral("angle_cmd_btn"));
        angle_cmd_btn->setGeometry(QRect(530, 320, 251, 27));
        label_13 = new QLabel(groupBox_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(352, 130, 61, 61));
        label_9 = new QLabel(groupBox_3);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 120, 261, 71));
        label_9->setWordWrap(true);
        robot_speed_ang_cmd = new QDoubleSpinBox(groupBox_3);
        robot_speed_ang_cmd->setObjectName(QStringLiteral("robot_speed_ang_cmd"));
        robot_speed_ang_cmd->setGeometry(QRect(270, 150, 81, 27));
        robot_speed_ang_cmd->setMinimum(-100);
        robot_speed_ang_cmd->setMaximum(100);
        robot_speed_ang_cmd_btn = new QPushButton(groupBox_3);
        robot_speed_ang_cmd_btn->setObjectName(QStringLiteral("robot_speed_ang_cmd_btn"));
        robot_speed_ang_cmd_btn->setGeometry(QRect(580, 140, 251, 27));
        line_4 = new QFrame(groupBox_3);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setGeometry(QRect(10, 120, 361, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        left_whell_speed_cmd_btn = new QPushButton(groupBox_3);
        left_whell_speed_cmd_btn->setObjectName(QStringLiteral("left_whell_speed_cmd_btn"));
        left_whell_speed_cmd_btn->setGeometry(QRect(580, 80, 251, 27));
        left_wheel_speed_cmd = new QDoubleSpinBox(groupBox_3);
        left_wheel_speed_cmd->setObjectName(QStringLiteral("left_wheel_speed_cmd"));
        left_wheel_speed_cmd->setGeometry(QRect(270, 90, 81, 27));
        left_wheel_speed_cmd->setDecimals(0);
        left_wheel_speed_cmd->setMinimum(-3000);
        left_wheel_speed_cmd->setMaximum(3000);
        left_wheel_speed_cmd->setSingleStep(10);
        label_14 = new QLabel(groupBox_3);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(10, 70, 261, 61));
        label_14->setWordWrap(true);
        label_15 = new QLabel(groupBox_3);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(352, 70, 61, 61));
        line_5 = new QFrame(groupBox_3);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setGeometry(QRect(10, 60, 361, 20));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);
        right_wheel_speed_cmd = new QDoubleSpinBox(groupBox_3);
        right_wheel_speed_cmd->setObjectName(QStringLiteral("right_wheel_speed_cmd"));
        right_wheel_speed_cmd->setGeometry(QRect(270, 30, 81, 27));
        right_wheel_speed_cmd->setDecimals(0);
        right_wheel_speed_cmd->setMinimum(-3000);
        right_wheel_speed_cmd->setMaximum(3000);
        right_wheel_speed_cmd->setSingleStep(10);
        label_16 = new QLabel(groupBox_3);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(10, 20, 261, 51));
        label_16->setWordWrap(true);
        right_whell_speed_cmd_btn = new QPushButton(groupBox_3);
        right_whell_speed_cmd_btn->setObjectName(QStringLiteral("right_whell_speed_cmd_btn"));
        right_whell_speed_cmd_btn->setGeometry(QRect(580, 30, 251, 27));
        label_17 = new QLabel(groupBox_3);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(352, 10, 61, 61));
        line_6 = new QFrame(groupBox_3);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setGeometry(QRect(410, 30, 20, 201));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(groupBox_3);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setGeometry(QRect(560, 30, 20, 201));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        label_26 = new QLabel(groupBox_3);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(420, 30, 151, 101));
        label_26->setAlignment(Qt::AlignCenter);
        label_26->setWordWrap(true);
        speed_consign_duration = new QSpinBox(groupBox_3);
        speed_consign_duration->setObjectName(QStringLiteral("speed_consign_duration"));
        speed_consign_duration->setGeometry(QRect(440, 140, 91, 26));
        speed_consign_duration->setMinimum(100);
        speed_consign_duration->setMaximum(20000);
        speed_consign_duration->setValue(1000);
        label_27 = new QLabel(groupBox_3);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(490, 130, 21, 41));
        label_27->setAlignment(Qt::AlignCenter);
        label_27->setWordWrap(true);
        line_8 = new QFrame(groupBox_3);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setGeometry(QRect(10, 350, 701, 20));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        label_18 = new QLabel(groupBox_3);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(20, 370, 61, 41));
        goto_X = new QSpinBox(groupBox_3);
        goto_X->setObjectName(QStringLiteral("goto_X"));
        goto_X->setGeometry(QRect(200, 380, 71, 26));
        goto_X->setMinimum(-3000);
        goto_X->setMaximum(3000);
        goto_X->setSingleStep(10);
        label_19 = new QLabel(groupBox_3);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(175, 380, 21, 21));
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(280, 380, 31, 21));
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(450, 380, 31, 21));
        goto_Y = new QSpinBox(groupBox_3);
        goto_Y->setObjectName(QStringLiteral("goto_Y"));
        goto_Y->setGeometry(QRect(370, 380, 71, 26));
        goto_Y->setMinimum(-3000);
        goto_Y->setMaximum(3000);
        goto_Y->setSingleStep(10);
        label_28 = new QLabel(groupBox_3);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(345, 380, 21, 21));
        goto_cmd_btn = new QPushButton(groupBox_3);
        goto_cmd_btn->setObjectName(QStringLiteral("goto_cmd_btn"));
        goto_cmd_btn->setGeometry(QRect(530, 380, 251, 27));
        dist_angle_controlmotor_control_2 = new QGroupBox(centralWidget);
        dist_angle_controlmotor_control_2->setObjectName(QStringLiteral("dist_angle_controlmotor_control_2"));
        dist_angle_controlmotor_control_2->setGeometry(QRect(890, 310, 171, 101));
        dist_angle_controlmotor_control_2->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        dist_angle_controlmotor_control_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        dist_angle_controlmotor_control_2->setFlat(true);
        distAngle_enable_btn = new QPushButton(dist_angle_controlmotor_control_2);
        distAngle_enable_btn->setObjectName(QStringLiteral("distAngle_enable_btn"));
        distAngle_enable_btn->setGeometry(QRect(30, 20, 99, 27));
        distAngle_disable_btn = new QPushButton(dist_angle_controlmotor_control_2);
        distAngle_disable_btn->setObjectName(QStringLiteral("distAngle_disable_btn"));
        distAngle_disable_btn->setGeometry(QRect(30, 60, 99, 27));
        group_reset = new QGroupBox(centralWidget);
        group_reset->setObjectName(QStringLiteral("group_reset"));
        group_reset->setGeometry(QRect(890, 440, 171, 71));
        group_reset->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        group_reset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        group_reset->setFlat(true);
        reset_btn = new QPushButton(group_reset);
        reset_btn->setObjectName(QStringLiteral("reset_btn"));
        reset_btn->setGeometry(QRect(30, 30, 99, 27));
        group_get_config = new QGroupBox(centralWidget);
        group_get_config->setObjectName(QStringLiteral("group_get_config"));
        group_get_config->setGeometry(QRect(830, 40, 141, 121));
        group_get_config->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        group_get_config->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        group_get_config->setFlat(true);
        get_config_btn = new QPushButton(group_get_config);
        get_config_btn->setObjectName(QStringLiteral("get_config_btn"));
        get_config_btn->setGeometry(QRect(20, 30, 99, 27));
        update_config_btn = new QPushButton(group_get_config);
        update_config_btn->setObjectName(QStringLiteral("update_config_btn"));
        update_config_btn->setGeometry(QRect(20, 80, 111, 27));
        group_reset_2 = new QGroupBox(centralWidget);
        group_reset_2->setObjectName(QStringLiteral("group_reset_2"));
        group_reset_2->setGeometry(QRect(910, 600, 131, 71));
        group_reset_2->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 9px;\n"
"    margin-top: 0.5em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        group_reset_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        group_reset_2->setFlat(true);
        goto_test_btn = new QPushButton(group_reset_2);
        goto_test_btn->setObjectName(QStringLiteral("goto_test_btn"));
        goto_test_btn->setGeometry(QRect(20, 30, 99, 27));
        AsservStreamControlPanel->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AsservStreamControlPanel);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1194, 22));
        AsservStreamControlPanel->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AsservStreamControlPanel);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        AsservStreamControlPanel->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AsservStreamControlPanel);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        AsservStreamControlPanel->setStatusBar(statusBar);

        retranslateUi(AsservStreamControlPanel);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(AsservStreamControlPanel);
    } // setupUi

    void retranslateUi(QMainWindow *AsservStreamControlPanel)
    {
        AsservStreamControlPanel->setWindowTitle(QApplication::translate("AsservStreamControlPanel", "AsservStreamControlPanel", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("AsservStreamControlPanel", "R\303\251glages asserv", Q_NULLPTR));
        vitesse_gauche_update_btn->setText(QApplication::translate("AsservStreamControlPanel", "Update", Q_NULLPTR));
        label_2->setText(QApplication::translate("AsservStreamControlPanel", "Vitesse Kp", Q_NULLPTR));
        label_3->setText(QApplication::translate("AsservStreamControlPanel", "Vitesse Ki", Q_NULLPTR));
        label_4->setText(QApplication::translate("AsservStreamControlPanel", "Range", Q_NULLPTR));
        vitesse_gauche_range_lb->setText(QApplication::translate("AsservStreamControlPanel", "Speed range = []", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_vitesse_gauche), QApplication::translate("AsservStreamControlPanel", "vitesse roue gauche", Q_NULLPTR));
        label_22->setText(QApplication::translate("AsservStreamControlPanel", "Range", Q_NULLPTR));
        label_23->setText(QApplication::translate("AsservStreamControlPanel", "Vitesse Ki", Q_NULLPTR));
        vitesse_droite_update_btn->setText(QApplication::translate("AsservStreamControlPanel", "Update", Q_NULLPTR));
        label_24->setText(QApplication::translate("AsservStreamControlPanel", "Vitesse Kp", Q_NULLPTR));
        vitesse_droite_range_lb->setText(QApplication::translate("AsservStreamControlPanel", "Speed range = []", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_vitesse_droite), QApplication::translate("AsservStreamControlPanel", "vitesse roue droite", Q_NULLPTR));
        label_5->setText(QApplication::translate("AsservStreamControlPanel", "Distance Kp", Q_NULLPTR));
        distance_update_btn->setText(QApplication::translate("AsservStreamControlPanel", "Update", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_distance), QApplication::translate("AsservStreamControlPanel", "Distance", Q_NULLPTR));
        label_25->setText(QApplication::translate("AsservStreamControlPanel", "Angle Kp", Q_NULLPTR));
        angle_update_btn->setText(QApplication::translate("AsservStreamControlPanel", "Update", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_angle), QApplication::translate("AsservStreamControlPanel", "Angle", Q_NULLPTR));
        angle_acc_update_btn->setText(QApplication::translate("AsservStreamControlPanel", "Update", Q_NULLPTR));
        label_29->setText(QApplication::translate("AsservStreamControlPanel", "Angle acceleration", Q_NULLPTR));
        label_32->setText(QApplication::translate("AsservStreamControlPanel", "mm/s\302\262", Q_NULLPTR));
        label_34->setText(QApplication::translate("AsservStreamControlPanel", "(Also left wheel acceleration limit for direct speed consign)", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_acc_angle), QApplication::translate("AsservStreamControlPanel", "Acceleration angle", Q_NULLPTR));
        label_33->setText(QApplication::translate("AsservStreamControlPanel", "mm/s\302\262", Q_NULLPTR));
        label_30->setText(QApplication::translate("AsservStreamControlPanel", "Distance max acceleration", Q_NULLPTR));
        distance_acc_update_btn->setText(QApplication::translate("AsservStreamControlPanel", "Update", Q_NULLPTR));
        label_31->setText(QApplication::translate("AsservStreamControlPanel", "(Also right wheel acceleration limit for direct speed consign)", Q_NULLPTR));
        label_49->setText(QApplication::translate("AsservStreamControlPanel", "mm/s\302\262", Q_NULLPTR));
        label_50->setText(QApplication::translate("AsservStreamControlPanel", "Distance min acceleration", Q_NULLPTR));
        label_51->setText(QApplication::translate("AsservStreamControlPanel", "mm/s", Q_NULLPTR));
        label_52->setText(QApplication::translate("AsservStreamControlPanel", "High speed threshold", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_acc_dist), QApplication::translate("AsservStreamControlPanel", "Acceleration distance", Q_NULLPTR));
        group_motor_control->setTitle(QApplication::translate("AsservStreamControlPanel", "Motor control", Q_NULLPTR));
        motor_enable_btn->setText(QApplication::translate("AsservStreamControlPanel", "Enable", Q_NULLPTR));
        motor_disable_btn->setText(QApplication::translate("AsservStreamControlPanel", "Disable", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("AsservStreamControlPanel", "Commandes ", Q_NULLPTR));
        label_6->setText(QApplication::translate("AsservStreamControlPanel", "Consigne position:", Q_NULLPTR));
        pos_cmd_btn->setText(QApplication::translate("AsservStreamControlPanel", "Send position command", Q_NULLPTR));
        label_7->setText(QApplication::translate("AsservStreamControlPanel", "Consigne vitesse avancement robot:", Q_NULLPTR));
        robot_speed_lin_cmd_btn->setText(QApplication::translate("AsservStreamControlPanel", "Send robot speed command", Q_NULLPTR));
        label_10->setText(QApplication::translate("AsservStreamControlPanel", "mm", Q_NULLPTR));
        label_12->setText(QApplication::translate("AsservStreamControlPanel", "mm/sec", Q_NULLPTR));
        label_11->setText(QApplication::translate("AsservStreamControlPanel", "rad", Q_NULLPTR));
        label_8->setText(QApplication::translate("AsservStreamControlPanel", "Consigne angle:", Q_NULLPTR));
        angle_cmd_btn->setText(QApplication::translate("AsservStreamControlPanel", "Send angle command", Q_NULLPTR));
        label_13->setText(QApplication::translate("AsservStreamControlPanel", "rad/sec", Q_NULLPTR));
        label_9->setText(QApplication::translate("AsservStreamControlPanel", "Consigne vitesse angulaire robot:", Q_NULLPTR));
        robot_speed_ang_cmd_btn->setText(QApplication::translate("AsservStreamControlPanel", "Send robot speed command", Q_NULLPTR));
        left_whell_speed_cmd_btn->setText(QApplication::translate("AsservStreamControlPanel", "Send wheel speed command", Q_NULLPTR));
        label_14->setText(QApplication::translate("AsservStreamControlPanel", "Consigne directe vitesse roue gauche:", Q_NULLPTR));
        label_15->setText(QApplication::translate("AsservStreamControlPanel", "mm/sec", Q_NULLPTR));
        label_16->setText(QApplication::translate("AsservStreamControlPanel", "Consigne directe vitesse roue droite:", Q_NULLPTR));
        right_whell_speed_cmd_btn->setText(QApplication::translate("AsservStreamControlPanel", "Send wheel speed command", Q_NULLPTR));
        label_17->setText(QApplication::translate("AsservStreamControlPanel", "mm/sec", Q_NULLPTR));
        label_26->setText(QApplication::translate("AsservStreamControlPanel", "Dur\303\251e consigne de vitesse", Q_NULLPTR));
        label_27->setText(QApplication::translate("AsservStreamControlPanel", "ms", Q_NULLPTR));
        label_18->setText(QApplication::translate("AsservStreamControlPanel", "GOTO:", Q_NULLPTR));
        label_19->setText(QApplication::translate("AsservStreamControlPanel", "X:", Q_NULLPTR));
        label_20->setText(QApplication::translate("AsservStreamControlPanel", "mm", Q_NULLPTR));
        label_21->setText(QApplication::translate("AsservStreamControlPanel", "mm", Q_NULLPTR));
        label_28->setText(QApplication::translate("AsservStreamControlPanel", "Y:", Q_NULLPTR));
        goto_cmd_btn->setText(QApplication::translate("AsservStreamControlPanel", "Send GOTO command", Q_NULLPTR));
        dist_angle_controlmotor_control_2->setTitle(QApplication::translate("AsservStreamControlPanel", "distance / angle control", Q_NULLPTR));
        distAngle_enable_btn->setText(QApplication::translate("AsservStreamControlPanel", "Enable", Q_NULLPTR));
        distAngle_disable_btn->setText(QApplication::translate("AsservStreamControlPanel", "Disable", Q_NULLPTR));
        group_reset->setTitle(QApplication::translate("AsservStreamControlPanel", "Reset", Q_NULLPTR));
        reset_btn->setText(QApplication::translate("AsservStreamControlPanel", "Reset", Q_NULLPTR));
        group_get_config->setTitle(QApplication::translate("AsservStreamControlPanel", "get config", Q_NULLPTR));
        get_config_btn->setText(QApplication::translate("AsservStreamControlPanel", "Get config", Q_NULLPTR));
        update_config_btn->setText(QApplication::translate("AsservStreamControlPanel", "update config", Q_NULLPTR));
        group_reset_2->setTitle(QApplication::translate("AsservStreamControlPanel", "Goto Test command", Q_NULLPTR));
        goto_test_btn->setText(QApplication::translate("AsservStreamControlPanel", "Goto Test", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AsservStreamControlPanel: public Ui_AsservStreamControlPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASSERVSTREAMCONTROLPANEL_H
