#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QDebug>
#include <QMessageBox>
#include "fonctions.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

extern  int argument_count;
extern  char** argument;
int dimension_x;
int dimension_y;
char **ecran;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    nb= 1;
}

Widget::~Widget()
{
    delete ui;
}

int lectureImage(void)
{
    FILE * fichier;
    char buffer[255];

    if (argument_count!=2) return 1;
    fichier= fopen(argument[1],"r");
    if (fichier==NULL) return 2;
do
    if( fgets (buffer, 255, fichier)==NULL ) return 3;
while (buffer[0]=='#');

    // ici on doit lire P1 sinon err 4
    if (((buffer[0]!='P') || (buffer[1]!='1') || (buffer[2]!='\n'))!=false) return 4;
// on attends les dimensions
    do
        if( fgets (buffer, 255, fichier)==NULL ) return 5;
    while (buffer[0]=='#');
    sscanf(buffer,"%d %d",&dimension_x,&dimension_y);
    ecran=(char **)malloc(sizeof(char)*dimension_x*dimension_y);
//ecran=argument;

qDebug()<<dimension_y*dimension_x;

    free(ecran);
    return EXIT_SUCCESS;
}

void drawImage(void)
{
    plot(10,10);
    if (argument_count==2) qDebug()<<argument[1];

}

void Widget::paintEvent(QPaintEvent *)
{
//    QPainter painter(this);
//    QPen pen(Qt::red);
//    pen.setWidth(2);
//    painter.setPen(pen);
//    painter.drawLine(0,0,100,100);


    int state;
    painter= new QPainter(this);
    QPen pen(Qt::red);
    pen.setWidth(2);
    painter->setPen(pen);


    state=lectureImage();

    if (state==1) QMessageBox::information(this,"Erreur","Erreur pas de nom de fichier ");
    if (state==2) QMessageBox::information(this,"Erreur","Pas lisible  ");
    if (state==3) QMessageBox::information(this,"Err","EOF  ");
    if (state==4) QMessageBox::information(this,"Err","Pas le bon format  ");
    if (state==5) QMessageBox::information(this,"Err","Pb dans la dimension.  ");


    //    drawImage();
//    resize(500,500);
    delete painter;
}

void Widget::mouseDoubleClickEvent(QMouseEvent *)
{
    nb++;
    if(nb>7)
        nb= 1;
    repaint();
    setWindowTitle("Image "+QString::number(nb));
}
