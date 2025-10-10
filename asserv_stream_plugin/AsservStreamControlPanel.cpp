#include "AsservStreamControlPanel.h"
#include "cborg/Cbor.h"
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
		printf("Error: Unable to send full command (wanted %ld sent %d)\n", length, size);

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
	uint8_t buffer[128];
	((uint32_t*)buffer)[0] =  0xBAADC0DE;
	
	Cbore encoder(&(buffer[4]), (std::size_t)(sizeof(buffer)-sizeof(uint32_t)));
	encoder.map()
		.key("name").item("speed_left")
		.key("Range_0")
			.array()
				.item(leftKp[0])
				.item(leftKi[0])
			.end()
		.key("Range_1")
			.array()
				.item(leftKp[1])
				.item(leftKi[1])
			.end()			
		.key("Range_2")
			.array()
				.item(leftKp[2])
				.item(leftKi[2])
			.end()			
	.end();
	encoder.print();
    send((char*)buffer, encoder.getLength()+sizeof(uint32_t) );
}

void AsservStreamControlPanel::on_vitesse_droite_update_btn_clicked()
{
	uint8_t buffer[128];
	((uint32_t*)buffer)[0] =  0xBAADC0DE;
	
	Cbore encoder(&(buffer[4]), (std::size_t)(sizeof(buffer)-sizeof(uint32_t)));
	encoder.map()
		.key("name").item("speed_right")
		.key("Range_0")
			.array()
				.item(rightKp[0])
				.item(rightKi[0])
			.end()
		.key("Range_1")
			.array()
				.item(rightKp[1])
				.item(rightKi[1])
			.end()			
		.key("Range_2")
			.array()
				.item(rightKp[2])
				.item(rightKi[2])
			.end()			
	.end();
	encoder.print();
    send((char*)buffer, encoder.getLength()+sizeof(uint32_t) );
}

void AsservStreamControlPanel::on_distance_update_btn_clicked()
{
	uint8_t buffer[128];
	((uint32_t*)buffer)[0] =  0xBAADC0DE;
	
	Cbore encoder(&(buffer[4]), (std::size_t)(sizeof(buffer)-sizeof(uint32_t)));
	encoder.map()
		.key("name").item("dist_regulator")
		.key("Kp").value( (float)ui_->distance_Kp->value())
	.end();
	encoder.print();
    send((char*)buffer, encoder.getLength()+sizeof(uint32_t) );

}
void AsservStreamControlPanel::on_angle_update_btn_clicked()
{
	uint8_t buffer[128];
	((uint32_t*)buffer)[0] =  0xBAADC0DE;
	
	Cbore encoder(&(buffer[4]), (std::size_t)(sizeof(buffer)-sizeof(uint32_t)));
	encoder.map()
		.key("name").item("angle_regulator")
		.key("Kp").value( (float)ui_->angle_Kp->value())
	.end();
	encoder.print();
    send((char*)buffer, encoder.getLength()+sizeof(uint32_t) );
}

void AsservStreamControlPanel::on_angle_acc_update_btn_clicked()
{
	uint8_t buffer[128];
	((uint32_t*)buffer)[0] =  0xBAADC0DE;
	
	Cbore encoder(&(buffer[4]), (std::size_t)(sizeof(buffer)-sizeof(uint32_t)));
	encoder.map()
		.key("name").item("angle_acc")
		.key("max_acc").value( (float)ui_->angle_acc->value())
	.end();
	encoder.print();
    send((char*)buffer, encoder.getLength()+sizeof(uint32_t) );
}

void AsservStreamControlPanel::on_distance_acc_update_btn_clicked()
{
	uint8_t buffer[128];
	((uint32_t*)buffer)[0] =  0xBAADC0DE;
	
	Cbore encoder(&(buffer[4]), (std::size_t)(sizeof(buffer)-sizeof(uint32_t)));
	encoder.map()
		.key("name").item("dist_acc")
		.key("max_acc").value( (float)ui_->dist_acc_max->value())
		.key("min_acc").value( (float)ui_->dist_acc_min->value())
		.key("highspeed_threshold").value( (float)ui_->dist_acc_threshold->value())
	.end();
	encoder.print();
    send((char*)buffer, encoder.getLength()+sizeof(uint32_t) );
}

void AsservStreamControlPanel::on_distance_acc_simple_update_btn_clicked()
{
	uint8_t buffer[128];
	((uint32_t*)buffer)[0] =  0xBAADC0DE;
	
	Cbore encoder(&(buffer[4]), (std::size_t)(sizeof(buffer)-sizeof(uint32_t)));
	encoder.map()
		.key("name").item("dist_acc")
		.key("max_acc").value( (float)ui_->dist_acc_simple_max->value())
	.end();
	encoder.print();
    send((char*)buffer, encoder.getLength()+sizeof(uint32_t) );
}

void AsservStreamControlPanel::on_distance_acc_dec_update_btn_clicked()
{
	uint8_t buffer[128];
	((uint32_t*)buffer)[0] =  0xBAADC0DE;
	
	Cbore encoder(&(buffer[4]), (std::size_t)(sizeof(buffer)-sizeof(uint32_t)));
	encoder.map()
		.key("name").item("dist_acc")
		.key("max_acc_fw").value( (float)ui_->dist_acc_fw->value())
		.key("max_acc_bw").value( (float)ui_->dist_acc_bw->value())
		.key("max_dec_fw").value( (float)ui_->dist_dec_fw->value())
		.key("max_dec_bw").value( (float)ui_->dist_dec_bw->value())
		.key("dampling").value( (float)ui_->dist_dampling->value())
	.end();
	encoder.print();
    send((char*)buffer, encoder.getLength()+sizeof(uint32_t) );
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
	const uint32_t synchroWord_config = 0xCAFEDECA;
    send((char*)&synchroWord_config, sizeof(synchroWord_config));
}

void AsservStreamControlPanel::on_update_config_btn_clicked()
{
	printf("Try to decode config buffer of size %d \n", uartDecoder->configBufferSize);
	Cborg top(uartDecoder->configBuffer, uartDecoder->configBufferSize);

	top.print();
	
	float valFloat=-1;
	std::string str;

	top.find("dist_regulator").find("Kp").getFloat(&valFloat);
	ui_->distance_Kp->setValue(valFloat);

	top.find("angle_regulator").find("Kp").getFloat(&valFloat);
	ui_->angle_Kp->setValue(valFloat);

	if( top.find("dist_acc").find("name").getString(str) ) 
	{
		
		if( str == "acc_limiter")
		{
			top.find("dist_acc").find("max_acc").getFloat(&valFloat);
			ui_->dist_acc_simple_max->setValue(valFloat);
		}
		else if ( str == "adv_acc_limiter")
		{
			top.find("dist_acc").find("max_acc").getFloat(&valFloat);
			ui_->dist_acc_max->setValue(valFloat);

			top.find("dist_acc").find("min_acc").getFloat(&valFloat);
			ui_->dist_acc_min->setValue(valFloat);

			top.find("dist_acc").find("highspeed_threshold").getFloat(&valFloat);
			ui_->dist_acc_threshold->setValue(valFloat);
		}
		else if( str == "acc_dec_limiter")
		{
			top.find("dist_acc").find("max_acc_fw").getFloat(&valFloat);
			ui_->dist_acc_fw->setValue(valFloat);

			top.find("dist_acc").find("max_dec_fw").getFloat(&valFloat);
			ui_->dist_dec_fw->setValue(valFloat);

			top.find("dist_acc").find("max_acc_bw").getFloat(&valFloat);
			ui_->dist_acc_bw->setValue(valFloat);

			top.find("dist_acc").find("max_dec_bw").getFloat(&valFloat);
			ui_->dist_dec_bw->setValue(valFloat);

			top.find("dist_acc").find("dampling").getFloat(&valFloat);
			ui_->dist_dampling->setValue(valFloat);
		}
	}


	if( top.find("angle_acc").find("name").getString(str) ) 
	{
		if( str == "acc_limiter")
		{
			top.find("angle_acc").find("max_acc").getFloat(&valFloat);
			ui_->angle_acc->setValue(valFloat);
		}
	}



	if( top.find("speed_right").find("name").getString(str) ) 
	{
		if( str == "adv_speed_ctrl")
		{
			top.find("speed_right").find("Range_0").at(0).getFloat(&valFloat);
			rightSpeedRange[0] = valFloat;
			top.find("speed_right").find("Range_1").at(0).getFloat(&valFloat);
			rightSpeedRange[1] = valFloat;
			top.find("speed_right").find("Range_2").at(0).getFloat(&valFloat);
			rightSpeedRange[2] = valFloat;

			top.find("speed_right").find("Range_0").at(1).getFloat(&valFloat);
			rightKp[0] = valFloat;
			top.find("speed_right").find("Range_1").at(1).getFloat(&valFloat);
			rightKp[1] = valFloat;
			top.find("speed_right").find("Range_2").at(1).getFloat(&valFloat);
			rightKp[2] = valFloat;

			top.find("speed_right").find("Range_0").at(2).getFloat(&valFloat);
			rightKi[0] = valFloat;
			top.find("speed_right").find("Range_1").at(2).getFloat(&valFloat);
			rightKi[1] = valFloat;
			top.find("speed_right").find("Range_2").at(2).getFloat(&valFloat);
			rightKi[2] = valFloat;
		}
	}

	ui_->vitesse_droite_Kp->setValue(rightKp[rightSpinBoxValue]);
	ui_->vitesse_droite_Ki->setValue(rightKi[rightSpinBoxValue]);
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



	if( top.find("speed_left").find("name").getString(str) ) 
	{
		if( str == "adv_speed_ctrl")
		{
			top.find("speed_left").find("Range_0").at(0).getFloat(&valFloat);
			leftSpeedRange[0] = valFloat;
			top.find("speed_left").find("Range_1").at(0).getFloat(&valFloat);
			leftSpeedRange[1] = valFloat;
			top.find("speed_left").find("Range_2").at(0).getFloat(&valFloat);
			leftSpeedRange[2] = valFloat;

			top.find("speed_left").find("Range_0").at(1).getFloat(&valFloat);
			leftKp[0] = valFloat;
			top.find("speed_left").find("Range_1").at(1).getFloat(&valFloat);
			leftKp[1] = valFloat;
			top.find("speed_left").find("Range_2").at(1).getFloat(&valFloat);
			leftKp[2] = valFloat;

			top.find("speed_left").find("Range_0").at(2).getFloat(&valFloat);
			leftKi[0] = valFloat;
			top.find("speed_left").find("Range_1").at(2).getFloat(&valFloat);
			leftKi[1] = valFloat;
			top.find("speed_left").find("Range_2").at(2).getFloat(&valFloat);
			leftKi[2] = valFloat;
		}
	}
	ui_->vitesse_gauche_Kp->setValue(leftKp[leftSpinBoxValue]);
	ui_->vitesse_gauche_Ki->setValue(leftKi[leftSpinBoxValue]);
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
}
