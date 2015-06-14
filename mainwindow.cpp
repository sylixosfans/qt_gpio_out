#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/select.h>
#include <sys/gpiofd.h>

/*
 *定义全局变量
*/
int  gLedFlag = 0;

/*
 * 系统生成的默认代码
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

/*    connect(ui->btnLed,SIGNAL(clicked()),this,SLOT(on_btnLed_clicked())); */
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
 * 用来实现按键“Led操作”的单击相应
*/
/**********************************************************************************************
 * GPIO LED测试，D601 = 136(faile)、D602 = 137(OK)、D603 = 138(OK)、D604 = 51(OK)、D605 = 52(OK);
 * gpio对应的数字代号在文件"s5pv210_gpio.h"里面。
 * GPIO 按键读取，Key6 = 155(OK)、Key7 = 156(OK)、Key8 = 157(OK)、Key9 = 158(OK)、Key0 = 159(OK);
 * gpio对应的数字代号在文件"s5pv210_gpio.h"里面。
 * GPIO第165号引脚，输出0101的方波信号
 **********************************************************************************************/
void MainWindow::on_btnLed_clicked()
{
    int       fdled;
//    uint8_t   iVal;
    int       gpioled5   = 52;
    /*
     * 打开 LED 的 GPIO 文件
     */
    fdled = gpiofd(gpioled5, O_WRONLY, GPIO_FLAG_OUT_INIT_LOW );
    if (fdled < 0) {
        perror("gpiofd create error!");
    }
    /*
     * 对gpio进行去反操作，首先读取当前gpio的状态，然后写入一个相反的状态
    */
    /*
    gpiofd_read(fdled,&iVal);

    if(iVal){
        gpiofd_write(fdled,0);
    }else{
        gpiofd_write(fdled,1);
    }
    */
    if(gLedFlag){
        gLedFlag = 0;
        gpiofd_write(fdled,0);
    }else{
        gLedFlag = 1;
        gpiofd_write(fdled,1);
    }

    QMessageBox::information(NULL, "GPIO Oper", "My works is down",
                             QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    ::close(fdled);

}
