#include "AudioPeak.h"
#include <algorithm>

using namespace Audio ;

AudioPeak::AudioPeak(float leftPeak, float rightPeak)
    :left(leftPeak), right(rightPeak)
{

}

AudioPeak::AudioPeak()
    :left(0), right(0){

}

void AudioPeak::update(const AudioPeak &other){
    if(other.left > left){
        left = other.left;
    }
    if(other.right > right){
        right = other.right;
    }
}

void AudioPeak::zero(){
    this->left = this->right = 0;
}

void AudioPeak::setLeft(float newLeftValue){
    this->left = newLeftValue;
}

void AudioPeak::setRight(float newRightValue){
    this->right = newRightValue;
}

float AudioPeak::max() const{
    return std::max(std::abs(left), std::abs(right));
}


