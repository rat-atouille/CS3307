// observerinterface.h
#ifndef OBSERVERINTERFACE_H
#define OBSERVERINTERFACE_H

class LayerObserver {
public:
    virtual void onLayerChanged() = 0;
    virtual ~LayerObserver() = default;
};

#endif // OBSERVERINTERFACE_H
