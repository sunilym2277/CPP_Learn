#include <iostream>
using namespace std;

enum ImageType{
    SATELLITE  = 0,
    DRONE 
};

class ImagePrototypeBase {
private:
    static ImagePrototypeBase  *prototypeList[10];
    static int prototypeCount;
public:
    virtual void draw() = 0;
    static ImagePrototypeBase  *createImageFromPrototype(ImageType type){
        for(int i =0 ; i < prototypeCount ; i++)
        {
            if(prototypeList[i]->getType() == type)
                return prototypeList[i]->clone();
        }
        return NULL;
    }
protected:
    virtual ImageType getType() = 0;
    virtual ImagePrototypeBase  *clone() = 0;
    static void registerPrototype(ImagePrototypeBase  *image){
        prototypeList[prototypeCount++] = image;
    }
};

ImagePrototypeBase  *ImagePrototypeBase ::prototypeList[]; // we need to define it outside of the class because we need to tell compile to alocate storage for that class
int ImagePrototypeBase ::prototypeCount = 0;

class SatelliteImage : public ImagePrototypeBase  {
private:
        int imageId;
        static int imageCounter;
        static SatelliteImage  prototypeInstance;
        SatelliteImage () { registerPrototype(this); }
protected:
        SatelliteImage (int dummy) { imageId = imageCounter++; }
public:
    ImageType getType() { return SATELLITE; }
    void draw() { cout<<"SATELLITE Image draw "<<imageId<<endl; }
    ImagePrototypeBase * clone() { return new SatelliteImage (1); }
};

class DroneImage : public ImagePrototypeBase  {
private:
    int imageId;
    static int imageCounter;
    static DroneImage  prototypeInstance;
    DroneImage () { registerPrototype (this); }
protected:
    DroneImage (int dummy) { imageId = imageCounter++; }    
public:
    ImageType getType() { return DRONE; }
    void draw() { cout<<"Done Image draw"<<imageId<<endl; }
    ImagePrototypeBase  *clone() { return new DroneImage (1); }


};

// Initialize static members for SatelliteImage
SatelliteImage SatelliteImage::prototypeInstance;
int SatelliteImage::imageCounter = 1;

// Initialize static members for DroneImage
DroneImage DroneImage::prototypeInstance;
int DroneImage::imageCounter = 1;



int main()
{
    ImagePrototypeBase  *images;
    images = ImagePrototypeBase ::createImageFromPrototype(SATELLITE);
    images->draw();

    images = ImagePrototypeBase ::createImageFromPrototype(SATELLITE);
    images->draw();

    images = ImagePrototypeBase ::createImageFromPrototype(SATELLITE);
    images->draw();

    images = ImagePrototypeBase ::createImageFromPrototype(SATELLITE);
    images->draw();

    images = ImagePrototypeBase::createImageFromPrototype(DRONE);
    images->draw();

    return 0;
}
