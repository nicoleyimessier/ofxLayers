//
//  Layer.hpp
//  LayerSystem
//
//  Created by Nicole Messier on 3/25/19.
//
//

#include "ofMain.h"
#include "MediaObject.h"

class Layer
{
public:
    
    Layer();
    ~Layer();
    
    void setup();
    void update(float dt);
    void draw();
    
    //! Visibility
    void setIsVisble(bool visible);
    
    //! Media Objects
    // Each layer should only have one background image, so this function should only be called once
    void addBgImage(string imgPath);
    
    //string _UID, ofVec2f _pos, int _zone, int _layer
    void addMediaObject(string UID,
                        ofVec2f pos,
                        int zone,
                        int layer);
    
private:
    
    //! Visibility
    bool isVisble = true;
    
    //! Media Objects
    ofImage * bgImage;
    bool hasBgImage = false; 
    
    //Replace this image with the media system
    vector<MediaObject*> mediaObjects;
};