#include "least_square_circle.h"

Least_square_circle::Least_square_circle(QWidget *parent):QLabel(parent)
{
    this->setMouseTracking(true);
}

void Least_square_circle::init_grid()
{
    /*Initialize Image Display Grid */

    this-> grid_elements.start_gridx= grid_size;
    this-> grid_elements.start_gridy=grid_size;
    this->grid_elements.end_gridx= this->size().width()-grid_elements.start_gridx;
    this->grid_elements.end_gridy=this->size().height()-grid_elements.start_gridy;
    this->grid_elements.x_inc=(int)((this->size().width()-2*grid_size)/grid_size);
    this->grid_elements.y_inc= (int)((this->size().width()-2*grid_size)/grid_size);

    /*assign dimentions to an image*/

    img= QImage(this->size().width(),this->size().height(),QImage::Format_RGB32);

    /*Initialize the image grid */
    this->reset_window(img);
}

void Least_square_circle::init_window()
{
    /*Fill the image with black color*/
    img.fill(qRgb(0, 0, 0));

   /*For all the grid point locations assign white color*/
   for(int i=grid_elements.start_gridx;i<grid_elements.end_gridx;i+=grid_elements.x_inc)
       for(int j=grid_elements.start_gridy;j<grid_elements.end_gridy;j+=grid_elements.y_inc)
             img.setPixel(i,j,qRgb(255,255,255));

    /*Modify label with an image*/
   this->setPixmap(QPixmap::fromImage(img));
}

void Least_square_circle::mousePressEvent(QMouseEvent *mouse_event)
{
    if(mouse_event->button()==Qt::LeftButton){
        QPoint mouse_pos= mouse_event->pos();
        emit sendMousepressPosition(mouse_pos);
    }
}

void Least_square_circle::reset_window(QImage &image_grid)
{
    /*Fill the image with black color*/
    image_grid.fill(qRgb(0,0,0));

    /*Assign image reference to painter*/
    QPainter painter(&image_grid);
    painter.setPen(QPen(Qt::white, 3));

    /*Assign white color to all grid point locations*/
    for(int i=grid_elements.start_gridx;i<grid_elements.end_gridx;i+=grid_elements.x_inc)  
        for(int j=grid_elements.start_gridy;j<grid_elements.end_gridy;j+=grid_elements.y_inc)
             painter.drawPoint(i,j);

    /*Modify label with an image*/
    this->setPixmap(QPixmap::fromImage(image_grid));
}


void Least_square_circle::point_toggle(QImage &image_grid,QPoint &p1)
{

    /* Assign image reference to painter */
    QPainter painter(&image_grid);


    /* The following for loop search the click point location  and  ckeck if it is white
    then convert it to blue and vice versa */

    for(int i=grid_elements.start_gridx;i<grid_elements.end_gridx;i+=grid_elements.x_inc)
    {
        for(int j=grid_elements.start_gridy;j<grid_elements.end_gridy;j+=grid_elements.y_inc)
          {
              if((p1.x()<=(i+3) && p1.x()>=(i-3)) && (p1.y()<=(j+3) && p1.y()>=(j-3))) {
                  QColor color(image_grid.pixel(i,j));

                  //condition to ckeck for white color
                  if(color.red()==255 && color.green()==255 && color.blue()==255){
                      cout<<"Inside white"<<endl;
                      painter.setPen(QPen(Qt::blue, 3));
                      painter.drawPoint(i,j);
                  }
                  // condition to check for blue color

                  if(color.red()==0 && color.green()==0 && color.blue()==255){
                      painter.setPen(QPen(Qt::white, 3));
                      painter.drawPoint(i,j);
                  }

              }
          }
     }

    /*Modify label with an image*/
    this->setPixmap(QPixmap::fromImage(image_grid));

}


void Least_square_circle::ls_circle(QImage &image_grid)
{


    /* Step - 1 collect all bule grid points */

    //--------+ Step 1 started
    QVector<QPoint> circle_points;
    for(int i=grid_elements.start_gridx;i<grid_elements.end_gridx;i+=grid_elements.x_inc)
    {
        for(int j=grid_elements.start_gridy;j<grid_elements.end_gridy;j+=grid_elements.y_inc)
        {
            QColor color(image_grid.pixel(i,j));
            if(color.red()==0 && color.green()==0 && color.blue()==255)
                circle_points.push_back(QPoint(i,j));
        }
    }     
    //--------+ Step 1 end

    double u_avg=0,v_avg=0;
    double ui[circle_points.size()],vi[circle_points.size()];
    double Suuu=0,Svvv=0,Suvv=0,Svuu=0,Suu=0,Svv=0,Suv=0,Su=0,Sv=0;

    /* Step - 2  calculate average location of x and y points */

     //--------+ Step 2 started
    for(int i=0;i<circle_points.size();i++){
        u_avg = u_avg + float(circle_points[i].x());
        v_avg += float(circle_points[i].y());
    }
   // cout<<" avg_1 "<<uavg<<" avg_2 "<<vavg<<endl;
    u_avg=u_avg/circle_points.size();
    v_avg=v_avg/circle_points.size();

    //--------+ Step 2 end


    //--------+ Step 3 started

    // mean subtractions
    for(int i=0;i<circle_points.size();i++)
    {
        ui[i]=double(circle_points[i].x())-u_avg;
        vi[i]=double(circle_points[i].y())-v_avg;
    }

    //--------+ Step 3 end


    //--------+ Step 4 started

    // least square circle parameters based on first and second derivative.
    for(int i=0;i<circle_points.size();i++)
    {
        Su += ui[i];Sv += vi[i];
        Suu += pow(ui[i],2); Svv += pow(vi[i],2);
        Suv += ui[i]*vi[i];
        Suuu += pow(ui[i],3);Svvv += pow(vi[i],3);
        Suvv += ui[i]*pow(vi[i],2); Svuu += vi[i]*pow(ui[i],2);
    }
    //--------+ Step 4 end


    //--------+ Step 5 started

    // find the solution of system of linear equations.

    // calculate the determinant.
    double detA= Suu*Svv-Suv*Suv;

    if(detA !=0)
    {
        //Calculate Adjoint of A
        double da= (1.0/detA);
        double A[2][2]={{da*Svv,da*(-Suv)},{da*(-Suv),da*Suu}};
        double B[2]={0.5*(Suvv+Suuu),0.5*(Svvv+Svuu)};

        // Calculate center and radius
        double x_center= (A[0][0]*B[0]+ A[0][1]*B[1]);
        double y_center= (A[1][0]*B[0]+ A[1][1]*B[1]);
        double radius=(x_center*x_center) +(y_center*y_center) + ((Suu+Svv)/(double)circle_points.size());
        radius =sqrt(radius);

        // Draw circle
        QRectF rectangle(x_center+u_avg-radius, y_center+v_avg-radius, 2*radius, 2*radius);
        QPainter painter(&image_grid);
        painter.setPen(QPen(Qt::blue, 2));
        painter.drawEllipse(rectangle);
    }

    this->setPixmap(QPixmap::fromImage(image_grid));
    //--------+ Step 5 end
}


