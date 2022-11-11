#include "AsservStreamControlPanel.h"

#include <unistd.h>  /* UNIX Standard Definitions      */

AsservStreamControlPanel::AsservStreamControlPanel(Ui_AsservStreamControlPanel *ui, AsservStream_uartDecoder *uartDecoder, int fd, int logFd ):
QMainWindow(),ui_(ui), fd_(fd), logFd_(logFd), uartDecoder(uartDecoder)
{
	ui->setupUi(this);
	connect(ui_->vitesse_gauche_range, SIGNAL(valueChanged(int)),
	    this, SLOT(on_spinboxLeftValueChanged(int)));
	connect(ui_->vitesse_droite_range, SIGNAL(valueChanged(int)),
	    this, SLOT(on_spinboxRightValueChanged(int)));

    leftSpinBoxValue = ui_->vitesse_gauche_range->value();
    rightSpinBoxValue = ui_->vitesse_droite_range->value();
    for(int i=0; i<3; i++)
    {
		leftKp[i] = 0;
		leftKi[i] = 0;
		rightKp[i] = 0;
		rightKi[i] = 0;
		leftSpeedRange[i] = 0;
		rightSpeedRange[i] = 0;
    }
}

void AsservStreamControlPanel::on_spinboxLeftValueChanged(int newLeftSpinBoxValue)
{
	leftKp[leftSpinBoxValue] = ui_->vitesse_gauche_Kp->value();
	leftKi[leftSpinBoxValue] = ui_->vitesse_gauche_Ki->value();
	leftSpinBoxValue = newLeftSpinBoxValue;
	ui_->vitesse_gauche_Kp->setValue(leftKp[leftSpinBoxValue]);
	ui_->vitesse_gauche_Ki->setValue(leftKi[leftSpinBoxValue]);
}

void AsservStreamControlPanel::on_spinboxRightValueChanged(int newrightSpinBoxValue)
{
	rightKp[rightSpinBoxValue] = ui_->vitesse_droite_Kp->value();
	rightKi[rightSpinBoxValue] = ui_->vitesse_droite_Ki->value();
	rightSpinBoxValue = newrightSpinBoxValue;
	ui_->vitesse_droite_Kp->setValue(rightKp[rightSpinBoxValue]);
	ui_->vitesse_droite_Ki->setValue(rightKi[rightSpinBoxValue]);
}

void AsservStreamControlPanel::send(char *buffer, size_t length)
{
	printf("Sending: \"%s\" \n",buffer);

	int size = write(fd_, buffer, length);
	if(size != length)
		printf("Error: Unable to send full command (wanted %d sent %ld)\n", length, size);

	if( logFd_ != -1 )
	{
	    size = write(logFd_, buffer, length);
	    (void) size;
	    size = write(logFd_, "\n", 1);
	    (void) size;
	}
}

void AsservStreamControlPanel::on_reset_btn_clicked()
{
    char buffer[] = "asserv reset";
    int len = sizeof(buffer);
    send(buffer, len);
}

void AsservStreamControlPanel::on_motor_enable_btn_clicked()
{
    char buffer[] = "asserv enablemotor 1";
    int len = sizeof(buffer);
    send(buffer, len);
}

void AsservStreamControlPanel::on_motor_disable_btn_clicked()
{
    char buffer[] = "asserv enablemotor 0";
    int len = sizeof(buffer);
    send(buffer, len);
}

void AsservStreamControlPanel::on_distAngle_enable_btn_clicked()
{
    char buffer[] = "asserv enablepolar 1";
    int len = sizeof(buffer);
    send(buffer, len);
}

void AsservStreamControlPanel::on_distAngle_disable_btn_clicked()
{
    char buffer[] = "asserv enablepolar 0";
    int len = sizeof(buffer);
    send(buffer, len);
}

void AsservStreamControlPanel::on_vitesse_gauche_update_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv speedcontrol l %s %s %s",
                      ui_->vitesse_gauche_Kp->text().toStdString().c_str(),
                      ui_->vitesse_gauche_Ki->text().toStdString().c_str(),
                      ui_->vitesse_gauche_range->text().toStdString().c_str() );
    send(buffer, len);
}

void AsservStreamControlPanel::on_vitesse_droite_update_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv speedcontrol r %s %s %s",
                      ui_->vitesse_droite_Kp->text().toStdString().c_str(),
                      ui_->vitesse_droite_Ki->text().toStdString().c_str(),
                      ui_->vitesse_droite_range->text().toStdString().c_str());
    send(buffer, len);
}

void AsservStreamControlPanel::on_distance_update_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv distcontrol %s",
                      ui_->distance_Kp->text().toStdString().c_str() );
    send(buffer, len);
}
void AsservStreamControlPanel::on_angle_update_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv anglecontrol %s",
                      ui_->angle_Kp->text().toStdString().c_str() );
    send(buffer, len);
}

void AsservStreamControlPanel::on_angle_acc_update_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv angleacc %s",
              ui_->angle_acc->text().toStdString().c_str() );
    send(buffer, len);
}

void AsservStreamControlPanel::on_distance_acc_update_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv distacc %s %s %s",
              ui_->dist_acc_max->text().toStdString().c_str(),
              ui_->dist_acc_min->text().toStdString().c_str(),
			  ui_->dist_acc_threshold->text().toStdString().c_str()
			  );
    send(buffer, len);
}

void AsservStreamControlPanel::on_distance_acc_dec_update_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv distaccdec %s %s %s %s %s",
              ui_->dist_acc_fw->text().toStdString().c_str(),
              ui_->dist_dec_fw->text().toStdString().c_str(),
			  ui_->dist_acc_bw->text().toStdString().c_str(),
			  ui_->dist_dec_bw->text().toStdString().c_str(),
			  ui_->dist_dampling->text().toStdString().c_str()

			  );
    send(buffer, len);
}


void AsservStreamControlPanel::on_robot_speed_lin_cmd_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv robotfwspeedstep %s %s", ui_->robot_speed_lin_cmd->text().toStdString().c_str(),
            ui_->speed_consign_duration->text().toStdString().c_str());
    send(buffer, len);
}

void AsservStreamControlPanel::on_robot_speed_ang_cmd_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv robotangspeedstep %s %s", ui_->robot_speed_ang_cmd->text().toStdString().c_str(),
            ui_->speed_consign_duration->text().toStdString().c_str());
    send(buffer, len);
}

void AsservStreamControlPanel::on_left_whell_speed_cmd_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv wheelspeedstep l %s %s", ui_->left_wheel_speed_cmd->text().toStdString().c_str(),
            ui_->speed_consign_duration->text().toStdString().c_str());
    send(buffer, len);
}

void AsservStreamControlPanel::on_right_whell_speed_cmd_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv wheelspeedstep r %s %s", ui_->right_wheel_speed_cmd->text().toStdString().c_str(),
            ui_->speed_consign_duration->text().toStdString().c_str());
    send(buffer, len);
}

void AsservStreamControlPanel::on_pos_cmd_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv adddist %s", ui_->pos_cmd->text().toStdString().c_str());
    send(buffer, len);
}

void AsservStreamControlPanel::on_angle_cmd_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv addangle %s", ui_->angle_cmd->text().toStdString().c_str());
    send(buffer, len);
}

void AsservStreamControlPanel::on_goto_cmd_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv addgoto %s %s", ui_->goto_X->text().toStdString().c_str(), ui_->goto_Y->text().toStdString().c_str());
    send(buffer, len);
}

void AsservStreamControlPanel::on_goto_test_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv gototest");
    send(buffer, len);
}


void AsservStreamControlPanel::on_get_config_btn_clicked()
{
    char buffer[128];
    int len = sprintf(buffer, "asserv get_config");
    send(buffer, len);
}

void AsservStreamControlPanel::on_update_config_btn_clicked()
{
	float *tab = (float*)uartDecoder->configBuffer;
	int index=0;

	leftKp[0] = tab[index++];
	leftKi[0] = tab[index++];
	leftSpeedRange[0] = tab[index++];
	leftKp[1] = tab[index++];
	leftKi[1] = tab[index++];
	leftSpeedRange[1] = tab[index++];
	leftKp[2] = tab[index++];
	leftKi[2] = tab[index++];
	leftSpeedRange[2] = tab[index++];

	rightKp[0] = tab[index++];
	rightKi[0] = tab[index++];
	rightSpeedRange[0] = tab[index++];
	rightKp[1] = tab[index++];
	rightKi[1] = tab[index++];
	rightSpeedRange[1] = tab[index++];
	rightKp[2] = tab[index++];
	rightKi[2] = tab[index++];
	rightSpeedRange[2] = tab[index++];


	ui_->distance_Kp->setValue(tab[index++]);
	ui_->angle_Kp->setValue(tab[index++]);

	ui_->angle_acc->setValue(tab[index++]);

	ui_->dist_acc_max->setValue(tab[index++]);
	ui_->dist_acc_min->setValue(tab[index++]);
	ui_->dist_acc_threshold->setValue(tab[index++]);
	// ui_->dist_acc_fw->setValue(tab[index++]);
	// ui_->dist_dec_fw->setValue(tab[index++]);
	// ui_->dist_acc_bw->setValue(tab[index++]);
	// ui_->dist_dec_bw->setValue(tab[index++]);
	// ui_->dist_dampling->setValue(tab[index++]);

	ui_->vitesse_gauche_Kp->setValue(leftKp[leftSpinBoxValue]);
	ui_->vitesse_gauche_Ki->setValue(leftKi[leftSpinBoxValue]);
	ui_->vitesse_droite_Kp->setValue(rightKp[rightSpinBoxValue]);
	ui_->vitesse_droite_Ki->setValue(rightKi[rightSpinBoxValue]);

	QString strLeft("Speed Range:   1=>[0;");
	strLeft.append(QString::number(leftSpeedRange[0]));
	strLeft.append("]   2=>[");
	strLeft.append(QString::number(leftSpeedRange[0]));
	strLeft.append(";");
	strLeft.append(QString::number(leftSpeedRange[1]));
	strLeft.append("]   3=>[");
	strLeft.append(QString::number(leftSpeedRange[1]));
	strLeft.append(";");
	strLeft.append(QString::number(leftSpeedRange[2]));
	strLeft.append("]");
	ui_->vitesse_gauche_range_lb->setText(strLeft);


	QString strRight("Speed Range:   1=>[0;");
	strRight.append(QString::number(rightSpeedRange[0]));
	strRight.append("]   2=>[");
	strRight.append(QString::number(rightSpeedRange[0]));
	strRight.append(";");
	strRight.append(QString::number(rightSpeedRange[1]));
	strRight.append("]   3=>[");
	strRight.append(QString::number(rightSpeedRange[1]));
	strRight.append(";");
	strRight.append(QString::number(rightSpeedRange[2]));
	strRight.append("]");
	ui_->vitesse_droite_range_lb->setText(strRight);

}
