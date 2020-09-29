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

#include <QWidget>
#include <QDialog>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QDebug>

#include "PointOp.h"
#include <Widgets/ImageListBox.h>
#include <Widgets/ImageWidgets/StandardImageWindow.h>
#include <Widgets/ImageWidgets/DoubleImageWindow.h>
#include <Converter.h>
#include "MyQLineEdit.h"
#include "../Tools.h"

using namespace std;
using namespace imagein;
using namespace genericinterface;

PointOp::PointOp() : GenericOperation(qApp->translate("Operations", "Pixel operations").toStdString()) {

}

PointOp::PixelOp* PointOp::PixelOp::fromString(QString op, QString expr) {
    if(op=="+") return new PixAdd(expr.toInt(0,0));
    if(op=="-") return new PixAdd(-expr.toInt(0,0));
    if(op=="*") return new PixMul(expr.toDouble());
    if(op=="/") return new PixMul(1/expr.toDouble());
    if(op=="& (bit-wise AND)") return new PixBitwiseAnd(expr.toUInt(0,0));
    if(op=="&& (logical AND)") return new PixLogicalAnd(expr.toUInt(0,0));
    if(op=="! (logical NOT)") return new PixLogicalNot(expr.toUInt(0,0));
    if(op=="| (bit-wise OR)") return new PixBitwiseOr(expr.toUInt(0,0));
    if(op=="|| (logical OR)") return new PixLogicalOr(expr.toUInt(0,0));
    if(op=="^ (bit-wise XOR)") return new PixBitwiseXor(expr.toUInt(0,0));
    if(op=="^^ (logical XOR)") return new PixLogicalXor(expr.toUInt(0,0));
    if(op=="<<") return new PixLshift(expr.toUInt(0,0));
    if(op==">>") return new PixRshift(expr.toUInt(0,0));
    if(op=="") return new PixIdent();
    std::cout << "Unknown operator '" << op.toStdString() << "' ! PixelOp" << std::endl;
    return new PixIdent();
}
PointOp::DoublePixelOp* PointOp::DoublePixelOp::fromString(QString op, QString expr) {
    if(op=="+") return new DoublePixAdd(expr.toDouble());
    if(op=="-") return new DoublePixAdd(-expr.toDouble());
    if(op=="*") return new DoublePixMul(expr.toDouble());
    if(op=="/") return new DoublePixMul(1/expr.toDouble());
    if(op=="&& (logical AND)") return new DoublePixLogicalAnd(expr.toUInt());
    if(op=="! (logical NOT)") return new DoublePixLogicalNot(expr.toUInt());
    if(op=="|| (logical OR)") return new DoublePixLogicalOr(expr.toUInt());
    if(op=="^^ (logical XOR)") return new DoublePixLogicalXor(expr.toUInt());
    if(op=="<<") return new DoublePixLshift(expr.toUInt());
    if(op==">>") return new DoublePixRshift(expr.toUInt());
    if(op=="") return new DoublePixIdent();
    std::cout << "Unknown operator '" << op.toStdString() << "' ! DoublePixelOp" << std::endl;
    return new DoublePixIdent();
}

PointOp::ImageOp* PointOp::ImageOp::fromString(QString op) {
    if(op=="+") return new ImgAdd();
    if(op=="-") return new ImgSub();
    if(op=="*") return new ImgMul();
    if(op=="/") return new ImgDiv();
    if(op=="& (bit-wise AND)") return new ImgBitwiseAnd();
    if(op=="&& (logical AND)") return new ImgLogicalAnd();
    if(op=="| (bit-wise OR)") return new ImgBitwiseOr();
    if(op=="|| (logical OR)") return new ImgLogicalOr();
    if(op=="^ (bit-wise XOR)") return new ImgBitwiseXor();
    if(op=="^^ (logical XOR)") return new ImgLogicalXor();
    if(op=="") return new ImgIdent();
    std::cout << "Unknown operator '" << op.toStdString() << "' ! ImageOp" << std::endl;
    return new ImgIdent();
}

PointOp::DoubleImageOp* PointOp::DoubleImageOp::fromString(QString op) {
    if(op=="+") return new DoubleImgAdd();
    if(op=="-") return new DoubleImgSub();
    if(op=="*") return new DoubleImgMul();
    if(op=="/") return new DoubleImgDiv();
    if(op=="&& (logical AND)") return new DoubleImgLogicalAnd();
    if(op=="|| (logical OR)") return new DoubleImgLogicalOr();
    if(op=="^^ (logical XOR)") return new DoubleImgLogicalXor();
    if(op=="") return new DoubleImgIdent();
    std::cout << "Unknown operator '" << op.toStdString() << "' ! DoubleImageOp" << std::endl;
    return new DoubleImgIdent();
}

void PointOp::operator()(const ImageWindow* currentWnd, const vector<const ImageWindow*>& wndList) {

    QStringList pixOperators, pixDoubleOperators, imgOperators, imgDoubleOperators;

    pixOperators << "" << "+" << "-" << "*" << "/" << qApp->translate("PointOp","! (bit-wise NOT)") << qApp->translate("PointOp","& (bit-wise AND)") << qApp->translate("PointOp","| (bit-wise OR)") << qApp->translate("PointOp","^ (bit-wise XOR)") << ">>" << "<<" << qApp->translate("PointOp","&& (logical AND)") << qApp->translate("PointOp","|| (logical OR)") << qApp->translate("PointOp","^^ (logical XOR)");
    pixDoubleOperators << "" << "+" << "-" << "*" << "/" << qApp->translate("PointOp","!! (logical NOT)") << qApp->translate("PointOp","&& (logical AND)") << qApp->translate("PointOp","|| (logical OR)") << qApp->translate("PointOp","^^ (logical XOR)");
    imgOperators << "" << "+" << "-" << "*" << "/" << qApp->translate("PointOp","& (bit-wise AND)") << qApp->translate("PointOp","| (bit-wise OR)") << qApp->translate("PointOp","^ (bit-wise XOR)") << qApp->translate("PointOp","&& (logical AND)") << qApp->translate("PointOp","|| (logical OR)") << qApp->translate("PointOp","^^ (logical XOR)");
    imgDoubleOperators << "" << "+" << "-" << "*" << "/" << qApp->translate("PointOp","&& (logical AND)") << qApp->translate("PointOp","|| (logical OR)") << qApp->translate("PointOp","^^ (logical XOR)");

    QString currentImgName = currentWnd->windowTitle();
    map<const Image*,string> stdImgList;
    map<const Image_t<double>*,string> dblImgList;
    for(vector<const ImageWindow*>::const_iterator it = wndList.begin(); it != wndList.end(); ++it) {
        if((*it)->isStandard()) {
            const StandardImageWindow* stdImgWnd = dynamic_cast<const StandardImageWindow*>(*it);
            stdImgList.insert(pair<const Image*, string>(stdImgWnd->getImage(), stdImgWnd->windowTitle().toStdString()));
        }
        else if((*it)->isDouble()) {
            const DoubleImageWindow* dblImgWnd = dynamic_cast<const DoubleImageWindow*>(*it);
            dblImgList.insert(pair<const Image_t<double>*, string>(dblImgWnd->getImage(), dblImgWnd->windowTitle().toStdString()));
        }
    }

    QDialog* dialog = new QDialog();
    dialog->setWindowTitle(qApp->translate("Operations", "Parameters"));
    dialog->setMinimumWidth(180);
    QVBoxLayout* layout = new QVBoxLayout();
    dialog->setLayout(layout);

    QGroupBox* radioGroup = new QGroupBox(qApp->translate("PointOp", "Second operand"), dialog);
    QRadioButton* valueButton = new QRadioButton(qApp->translate("PointOp", "Value"));
    valueButton->setWhatsThis(qApp->translate("PointOp", "Enter a real number in the blank space below as the second operand"));
    QRadioButton* imageButton = new QRadioButton(qApp->translate("PointOp", "Image"));
    imageButton->setWhatsThis(qApp->translate("PointOp", "Select an image as the second operand"));

    QGroupBox* radioGroup2 = new QGroupBox(qApp->translate("PointOp", "Output image"), dialog);
    QRadioButton* uCharButton = new QRadioButton(qApp->translate("PointOp", "UChar"));
    uCharButton->setWhatsThis(qApp->translate("PointOp", "Output the result image in uchar format"));
    QRadioButton* doubleButton = new QRadioButton(qApp->translate("PointOp", "Double"));
    doubleButton->setWhatsThis(qApp->translate("PointOp", "Output the result image in double format"));

    QHBoxLayout* radioLayout = new QHBoxLayout(radioGroup);
    radioLayout->addWidget(valueButton);
    radioLayout->addWidget(imageButton);

    QHBoxLayout* radioLayout2 = new QHBoxLayout(radioGroup2);
    radioLayout2->addWidget(uCharButton);
    radioLayout2->addWidget(doubleButton);

    layout->addWidget(radioGroup);
    layout->addWidget(radioGroup2);
    valueButton->setChecked(true);
    uCharButton->setChecked(true);

    //Si l'image est une image double le bouton est obligatoirement coché
    if(currentWnd->isDouble()){
        doubleButton->setChecked(true);
        doubleButton->setEnabled(false);
        uCharButton->setEnabled(false);
    }

    QGroupBox* checkbox = new QGroupBox(qApp->translate("PointOp","Options"));
    QHBoxLayout* optLayout = new QHBoxLayout();
    QGridLayout* gridLayout = new QGridLayout();
    QCheckBox* offsetBox = new QCheckBox(qApp->translate("PointOp","Offset"));
    offsetBox->setWhatsThis(qApp->translate("PointOp", "Add an offset of 127"));
    QCheckBox* scalingBox = new QCheckBox(qApp->translate("PointOp","Scaling"));
    scalingBox->setWhatsThis(qApp->translate("PointOp", "Map the value of each pixel to the range of 0-255 proportionally"));
    QCheckBox* colorBox = new QCheckBox(qApp->translate("PointOp", "Explode colors"));
    colorBox->setWhatsThis(qApp->translate("PointOp", "Check this option to execute the manipulation by channel"));
    offsetBox->setAutoExclusive(false);
    scalingBox->setAutoExclusive(false);
    offsetBox->setEnabled(!doubleButton->isChecked());
    scalingBox->setEnabled(!doubleButton->isChecked());
    offsetBox->setChecked(doubleButton->isChecked());
    scalingBox->setChecked(doubleButton->isChecked());
    colorBox->setAutoExclusive(false);
    optLayout->addWidget(offsetBox);
    optLayout->addWidget(scalingBox);

    gridLayout->addLayout(optLayout,1,1);
    gridLayout->addWidget(colorBox,2,1);

    checkbox->setLayout(gridLayout);
    layout->addWidget(checkbox);

    int nChannel = currentWnd->getDisplayImage()->getNbChannels();

    QHBoxLayout** valueLayouts = new QHBoxLayout*[nChannel+1];
    QComboBox** pixOperatorBoxes = new QComboBox*[nChannel+1];
    QComboBox** imgOperatorBoxes = new QComboBox*[nChannel+1];
    MyQLineEdit** exprEdits = new MyQLineEdit*[nChannel+1];
    MixImageListBox** imageBoxes = new MixImageListBox*[nChannel+1];

    QWidget* pixelWidget = new QWidget(dialog);
    QWidget* imgWidget = new QWidget(dialog);
    valueLayouts[0] = new QHBoxLayout();
    pixOperatorBoxes[0] = new QComboBox(pixelWidget);
    imgOperatorBoxes[0] = new QComboBox(imgWidget);

    if(currentWnd->isStandard()){
        pixOperatorBoxes[0]->addItems(pixOperators);
        imgOperatorBoxes[0]->addItems(imgOperators);
    }else{
        pixOperatorBoxes[0]->addItems(pixDoubleOperators);
        imgOperatorBoxes[0]->addItems(imgDoubleOperators);
    }

    exprEdits[0] = new MyQLineEdit(pixelWidget);
    exprEdits[0]->setFixedWidth(64);
/*************************************************************/
/*Overwrite QLineEdit class, send signals according to the change of combobox content to determine the corresponding supported input data type*/
    QObject::connect(pixOperatorBoxes[0], SIGNAL(currentTextChanged(QString)), exprEdits[0], SLOT(updateValidator(QString)));
    QObject::connect(imgOperatorBoxes[0], SIGNAL(currentTextChanged(QString)), exprEdits[0], SLOT(updateValidator(QString)));
/*************************************************************/
    imageBoxes[0] = new MixImageListBox(pixelWidget, currentImgName.toStdString(), stdImgList, dblImgList);
    valueLayouts[0]->addWidget(new QLabel(currentImgName, pixelWidget));
    valueLayouts[0]->addWidget(pixOperatorBoxes[0]);
    valueLayouts[0]->addWidget(imgOperatorBoxes[0]);
    valueLayouts[0]->addWidget(exprEdits[0]);
    valueLayouts[0]->addWidget(imageBoxes[0]);
    imageBoxes[0]->setVisible(false);
    imgOperatorBoxes[0]->setVisible(false);
    pixelWidget->setLayout(valueLayouts[0]);
    layout->addWidget(pixelWidget);

    QWidget* colorWidget = new QWidget(dialog);
    colorWidget->setLayout(new QVBoxLayout());
    for(int i=1; i <= nChannel; ++i) {
        valueLayouts[i] = new QHBoxLayout();
        pixOperatorBoxes[i] = new QComboBox(colorWidget);
        imgOperatorBoxes[i] = new QComboBox(colorWidget);
        if(currentWnd->isStandard()){
            pixOperatorBoxes[i]->addItems(pixOperators);
            imgOperatorBoxes[i]->addItems(imgOperators);
        }else{
            pixOperatorBoxes[i]->addItems(pixDoubleOperators);
            imgOperatorBoxes[i]->addItems(imgDoubleOperators);
        }
        exprEdits[i] = new MyQLineEdit(colorWidget);
        exprEdits[i]->setFixedWidth(64);
        QObject::connect(pixOperatorBoxes[i], SIGNAL(currentTextChanged(QString)), exprEdits[i], SLOT(updateValidator(QString)));
        QObject::connect(imgOperatorBoxes[i], SIGNAL(currentTextChanged(QString)), exprEdits[i], SLOT(updateValidator(QString)));
        imageBoxes[i] = new MixImageListBox(colorWidget, currentImgName.toStdString(), stdImgList, dblImgList);
        valueLayouts[i]->addWidget(new QLabel(currentImgName+"::"+Tools::colorName(i-1, nChannel), colorWidget));
        valueLayouts[i]->addWidget(pixOperatorBoxes[i]);
        valueLayouts[i]->addWidget(imgOperatorBoxes[i]);
        valueLayouts[i]->addWidget(exprEdits[i]);
        valueLayouts[i]->addWidget(imageBoxes[i]);
        imageBoxes[i]->setVisible(false);
        imgOperatorBoxes[i]->setVisible(false);
        colorWidget->layout()->addItem(valueLayouts[i]);
    }
    colorWidget->setVisible(false);
    layout->addWidget(colorWidget);

    for(int i=0; i<=nChannel; ++i) {
        QObject::connect(valueButton, SIGNAL(toggled(bool)), exprEdits[i], SLOT(setVisible(bool)));
        QObject::connect(valueButton, SIGNAL(toggled(bool)), pixOperatorBoxes[i], SLOT(setVisible(bool)));
        QObject::connect(imageButton, SIGNAL(toggled(bool)), imageBoxes[i], SLOT(setVisible(bool)));
        QObject::connect(imageButton, SIGNAL(toggled(bool)), imgOperatorBoxes[i], SLOT(setVisible(bool)));
    }
    QObject::connect(colorBox, SIGNAL(toggled(bool)), pixelWidget, SLOT(setHidden(bool)));
    QObject::connect(colorBox, SIGNAL(toggled(bool)), colorWidget, SLOT(setVisible(bool)));
    QObject::connect(uCharButton, SIGNAL(toggled(bool)), offsetBox, SLOT(setEnabled(bool)));
    QObject::connect(uCharButton, SIGNAL(toggled(bool)), scalingBox, SLOT(setEnabled(bool)));
    QObject::connect(doubleButton, SIGNAL(toggled(bool)), offsetBox, SLOT(setChecked(bool)));
    QObject::connect(doubleButton, SIGNAL(toggled(bool)), scalingBox, SLOT(setChecked(bool)));

    layout->setSizeConstraint(QLayout::SetFixedSize);
    
    QPushButton *okButton = new QPushButton(qApp->translate("Operations", "Validate"), dialog);
    okButton->setDefault(true);
    layout->addWidget(okButton);
    QObject::connect(okButton, SIGNAL(clicked()), dialog, SLOT(accept()));
    
    QDialog::DialogCode code = static_cast<QDialog::DialogCode>(dialog->exec());
    
    if(code!=QDialog::Accepted) {
        return;
    }

    bool dblResult = currentWnd->isDouble() || doubleButton->isChecked();
    if(!valueButton->isChecked()) {
        if(!colorBox->isChecked()) {
            dblResult = dblResult || (imageBoxes[0]->currentType() == MixImageListBox::DBLIMG);
        }
        else {
            for(int i=0; i<nChannel; ++i) {
                dblResult = dblResult || (imageBoxes[i+1]->currentType() == MixImageListBox::DBLIMG);
            }
        }
    }

    const DoubleImageWindow* currentDblWnd = dynamic_cast<const DoubleImageWindow*>(currentWnd);
    const Image_t<double>* image = currentDblWnd ? Converter<Image_t<double> >::convert(*currentDblWnd->getImage()) : Converter<Image_t<double> >::convert(*currentWnd->getDisplayImage());
    unsigned int maxWidth = image->getWidth();
    unsigned int maxHeight = image->getHeight();

    Image_t<double>* resDoubleImg;
    Image* resImg;

    if(valueButton->isChecked()) {
        PixelOp** pixelOps = new PixelOp*[nChannel];
        DoublePixelOp** doublePixelOps = new DoublePixelOp*[nChannel];
        if(!colorBox->isChecked()) {
            QString expr = exprEdits[0]->text();
            PixelOp* pixelOp = PixelOp::fromString(pixOperatorBoxes[0]->currentText(), expr);
            DoublePixelOp* doublePixelOp = DoublePixelOp::fromString(pixOperatorBoxes[0]->currentText(), expr);
            for(int i=0; i<nChannel; ++i){
                pixelOps[i] = pixelOp;
                doublePixelOps[i] = doublePixelOp;
            }
        }
        else {
            for(int i=0; i<nChannel; ++i) {
                QString expr = exprEdits[i+1]->text();
                pixelOps[i] = PixelOp::fromString(imgOperatorBoxes[i+1]->currentText(), expr);
                doublePixelOps[i] = DoublePixelOp::fromString(imgOperatorBoxes[i+1]->currentText(), expr);
            }
        }

        resImg = new Image(image->getWidth(), image->getHeight(), nChannel);
        resDoubleImg = new Image_t<double>(image->getWidth(), image->getHeight(), nChannel);
        for(int c = 0; c < nChannel; ++c) {
            for(unsigned int j = 0; j < image->getHeight(); ++j) {
                for(unsigned int i = 0; i < image->getWidth(); ++i) {
                    if(dblResult){
                        double value1 = image->getPixel(i, j, c);
                        double value2 = doublePixelOps[c]->operator()(value1);
                        resDoubleImg->setPixel(i, j, c, value2);
                    }else{
                        int value1 = image->getPixel(i, j, c);
                        int value2 = pixelOps[c]->operator()(value1);
                        resImg->setPixel(i, j, c, value2);
                    }
                }
            }
        }
    }
    else {
        /*The double image process exist already, but cases of standard images is ignored*/
        ImageOp** stdImageOps = new ImageOp*[nChannel];
        DoubleImageOp** dblImageOps = new DoubleImageOp*[nChannel];

        bool isDblImg[nChannel];
        const Image_t<double>* dblImageImgs[nChannel];
        const Image* stdImageImgs[nChannel];
        if(!colorBox->isChecked()) {
            DoubleImageOp* dblImageOp = DoubleImageOp::fromString(imgOperatorBoxes[0]->currentText());
            ImageOp* stdImageOp = ImageOp::fromString(imgOperatorBoxes[0]->currentText());
            for(int i=0; i<nChannel; ++i){
                stdImageOps[i] = stdImageOp;
                dblImageOps[i] = dblImageOp;
            }
            if(imageBoxes[0]->currentType() == MixImageListBox::DBLIMG) {
                const Image_t<double>* dblImg = imageBoxes[0]->getDblImage(imageBoxes[0]->currentText().toStdString());
                for(int i=0; i<nChannel; ++i) {
                    dblImageImgs[i] = dblImg;
                    isDblImg[i] = true;
                }
                maxWidth = min(maxWidth, dblImg->getWidth());
                maxHeight = min(maxHeight, dblImg->getHeight());
            }
            else {
                const Image* stdImg = imageBoxes[0]->getStdImage(imageBoxes[0]->currentText().toStdString());
                for(int i=0; i<nChannel; ++i) {
                    stdImageImgs[i] = stdImg;
                    isDblImg[i] = false;
                }
                maxWidth = min(maxWidth, stdImg->getWidth());
                maxHeight = min(maxHeight, stdImg->getHeight());
            }
        }
        else {
            for(int i=0; i<nChannel; ++i) {
                stdImageOps[i] = ImageOp::fromString(imgOperatorBoxes[i+1]->currentText());
                dblImageOps[i] = DoubleImageOp::fromString(imgOperatorBoxes[i+1]->currentText());
                if(imageBoxes[i+1]->currentType() == MixImageListBox::DBLIMG) {
                    const Image_t<double>* dblImg = imageBoxes[i+1]->getDblImage(imageBoxes[i+1]->currentText().toStdString());
                    for(int i=0; i<nChannel; ++i) {
                        dblImageImgs[i] = dblImg;
                        isDblImg[i] = true;
                    }
                    maxWidth = min(maxWidth, dblImg->getWidth());
                    maxHeight = min(maxHeight, dblImg->getHeight());
                }
                else {
                    const Image* stdImg = imageBoxes[i+1]->getStdImage(imageBoxes[i+1]->currentText().toStdString());
                    for(int i=0; i<nChannel; ++i) {
                        stdImageImgs[i] = stdImg;
                        isDblImg[i] = false;
                    }
                    maxWidth = min(maxWidth, stdImg->getWidth());
                    maxHeight = min(maxHeight, stdImg->getHeight());
                }
            }
        }

        resImg = new Image(maxWidth, maxHeight, nChannel);
        resDoubleImg = new Image_t<double>(maxWidth, maxHeight, nChannel);
        for(int c = 0; c < resImg->getNbChannels(); ++c) {
            for(unsigned int j = 0; j < resImg->getHeight(); ++j) {
                for(unsigned int i = 0; i < resImg->getWidth(); ++i) {
                    if(isDblImg[c]) {
                        double value1 = image->getPixel(i, j, c);
                        const unsigned int channel = (c < dblImageImgs[c]->getNbChannels() ? c : 0);
                        double value2 = dblImageImgs[c]->getPixel(i, j, channel);
                        double resVal = dblImageOps[c]->operator()(value1, value2);
                        resDoubleImg->setPixel(i, j, c, resVal);
                    }
                    else {
                        int value1 = image->getPixel(i, j, c);
                        const unsigned int channel = (c < stdImageImgs[c]->getNbChannels() ? c : 0);
                        int value2 = stdImageImgs[c]->getPixel(i, j, channel);
                        int resVal = stdImageOps[c]->operator()(value1, value2);
                        resImg->setPixel(i, j, c, resVal);
                    }
                }
            }
        }
    }

    if(dblResult) {
        if(currentDblWnd) {
            this->outDoubleImage(resDoubleImg, "", currentDblWnd->isNormalized(), currentDblWnd->isLogScaled());
        }
        else {
            this->outDoubleImage(resDoubleImg, "", false, false);
        }
        delete image;
    }
    else {
        Image* charResImg;
        bool _scaling = scalingBox->isChecked();
        bool _offset = offsetBox->isChecked();
        std::string outputMessage = "";
        Image_t<int>* intResImg = Converter<Image_t<int> >::convert(*resImg);
        if(_scaling && _offset ){
            charResImg  =  Converter<Image>::convertScaleAndOffset(*intResImg, &outputMessage);
        }
        else if(_scaling){
            charResImg =  Converter<Image>::convertAndScale(*intResImg, &outputMessage);
        }
        else if(_offset){
            charResImg = Converter<Image>::convertAndOffset(*intResImg, &outputMessage);
        }
        else{
            charResImg = Converter<Image>::convert(*resImg);
            outputMessage = qApp->translate("Operations","Pas de conversion [min : 0, max : 255]").toStdString();
        }
        this->outText(outputMessage);
        this->outText("-------------------------------------------");

        this->outImage(charResImg);
    }
}

bool PointOp::needCurrentImg() const {
    return true;
}

bool PointOp::isValidImgWnd(const genericinterface::ImageWindow* imgWnd) const {
    return imgWnd != NULL;
}
