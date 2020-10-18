/*
 * Copyright 2011-2012 INSA Rennes
 *
 * This file is part of ImageINSA.
 *
 * ImageINSA is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ImageINSA is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ImageINSA.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Operation.h"
#include <Widgets/ImageWidgets/StandardImageWindow.h>
#include <Widgets/ImageWidgets/DoubleImageWindow.h>
#include <Services/WindowService.h>
#include "../app/Operations/HoughOp.h"
#include <QString>

using namespace std;
using namespace imagein;
using namespace genericinterface;
#include "Services/WindowService.h"
#include "Services/Node.h"

class ImageINSAService : public genericinterface::WindowService
{
public:
    void outputText(QString text);
};

void GenericOperation::operator()(WindowService* ws) {
        _ws = ws;
        _curImgWnd = ws->getCurrentImageWindow();
        vector<const ImageWindow*> wndList = ws->getImageWindows();
        return this->operator ()(_curImgWnd, wndList);
}

void GenericOperation::outImgWnd(ImageWindow* imgWnd, string title) {
        if(_ws == NULL) return;
        NodeId id;
        QString path;
        QString wndTitle;
        if(this->needCurrentImg()) {
                path = _curImgWnd->getPath();
                id = _ws->getNodeId(_curImgWnd);
                wndTitle = _curImgWnd->windowTitle() + " - ";
        }
        else {
                path = "";
                id = NodeId(imgWnd->getDisplayImage());
                wndTitle = "";
        }

        if(title.size() == 0) title = this->getName();
        imgWnd->setPath(path);
        imgWnd->setWindowTitle(wndTitle + title.c_str());
        _ws->addImage(id, imgWnd);
}

void GenericOperation::outImage(imagein::Image* img, string title) {
        StandardImageWindow* wnd = new StandardImageWindow(img);
        this->outImgWnd(wnd, title);
}

void GenericOperation::outDoubleImage(imagein::ImageDouble* img, string title, bool norm, bool log, double logScale, bool abs) {
        DoubleImageWindow* wnd = new DoubleImageWindow(img, QString(), norm, log, logScale, abs);
        /*Transmissed through the customized signal, the messages generated by Doubleimage window can be output to the information bar*/
        QObject::connect(wnd, SIGNAL(textToShow(QString)), this->_ws, SLOT(outputText(QString)));
        if(HoughOp* v = dynamic_cast<HoughOp*>(this)) {
                // teste si l'operation effectuee est une transformee de Hough
                if (v->hough1()) {
                        wnd->isHough(1, 1);
                }else{
                        wnd->isHough(v->getAngleStep(), v->getDistanceStep());
                }
                //isHough=true ce qui change les coordonnées des pixels de l'image pour correspondre au domaine de Hough
        }
        this->outImgWnd(wnd, title);
        if(img->min()<0){
            std::string outputMessage = qApp->translate("Operation","Both Offset and Scaling applied : val_display = (127-minValue) > (maxValue-127) ? val_image * 127 / (- minValue) + 127 : val_image * 128 / maxValue + 127\n\n-------------------------------------------").toStdString();
            outText(outputMessage);
        }
}

void GenericOperation::outText(std::string text) {
        if(_ws == NULL) return;
        _ws->addText(text);
}

void Operation::operator()(const ImageWindow* currentWnd, const vector<const ImageWindow*>& wndList) {
        const StandardImageWindow* curImgWnd = dynamic_cast<const StandardImageWindow*>(currentWnd);
        const Image* image = curImgWnd ? curImgWnd->getImage() : NULL;
        const Image* curImg = image;
        vector<const Image*> imgToDelete;
        if(curImgWnd) {
                Rectangle select = curImgWnd->selection();
                if(select.x>0 || select.y>0 || select.w<(image->getWidth()-1) || select.h<(image->getHeight()-1)) {
                        if((select.x+select.w)<image->getWidth() && (select.y+select.h)<image->getHeight()) {
                                image = image->crop(select);
                                imgToDelete.push_back(image);
                        }
                }
        }

        map<const Image*, string> imgList;
        for(vector<const ImageWindow*>::const_iterator it = wndList.begin(); it != wndList.end(); ++it) {
                const StandardImageWindow* imgWnd = dynamic_cast<const StandardImageWindow*>(*it);
                if(imgWnd) {
                        const Image* img = imgWnd->getImage();
                        if(img == curImg) img = image;
                        imgList.insert(pair<const Image*, string>(img, imgWnd->windowTitle().toStdString()));
                }
        }

        this->operator()(image, imgList);

        for(vector<const Image*>::iterator it = imgToDelete.begin(); it < imgToDelete.end(); ++it) {
                delete *it;
        }
}

bool Operation::isValidImgWnd(const genericinterface::ImageWindow* imgWnd) const {
        return (dynamic_cast<const StandardImageWindow*>(imgWnd) != NULL);
}

void DoubleOperation::operator()(const ImageWindow* currentWnd, const vector<const ImageWindow*>& wndList) {
        const DoubleImageWindow* curImgWnd = dynamic_cast<const DoubleImageWindow*>(currentWnd);
        const Image_t<double>* image = curImgWnd ? curImgWnd->getImage() : NULL;
        map<const Image_t<double>*, string> imgList;
        for(vector<const ImageWindow*>::const_iterator it = wndList.begin(); it != wndList.end(); ++it) {
                const DoubleImageWindow* imgWnd = dynamic_cast<const DoubleImageWindow*>(*it);
                if(imgWnd) {
                        imgList.insert(pair<const Image_t<double>*, string>(imgWnd->getImage(), imgWnd->windowTitle().toStdString()));
                }
        }
        return this->operator()(image, imgList);
}

bool DoubleOperation::isValidImgWnd(const genericinterface::ImageWindow* imgWnd) const {
        return (dynamic_cast<const DoubleImageWindow*>(imgWnd) != NULL);
}
