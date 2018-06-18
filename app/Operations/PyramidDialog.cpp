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

#include "PyramidDialog.h"
#include "ui_PyramidDialog.h"

PyramidDialog::PyramidDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PyramidDialog)
{
    ui->setupUi(this);
}

PyramidDialog::~PyramidDialog()
{
    delete ui;
}

Pyramid::Filtre PyramidDialog::getFilter() const {
    Pyramid::Filters filters;
    Pyramid::Filtre filter;
    switch(ui->filterBox->currentIndex()) {
        case 1: filters.getFromName("gaussien", filter); break;
        case 2: filters.getFromName("trimodal", filter); break;
        case 3: filters.getFromName("rectangulaire", filter); break;
        case 4: filters.getFromName("qmf", filter); break;
        default: filters.getFromName("triangulaire", filter); break;
    }
    return filter;
}

int PyramidDialog::getNbStep() {
    return ui->stepBox->value();
}

bool PyramidDialog::isGaussian() const {
    return ui->gaussianButton->isChecked();
}

bool PyramidDialog::onlyOneStep() const {
    return ui->oneStepBox->isChecked();
}

int PyramidDialog::onlyStep() const {
    return ui->onlyStepBox->value();
}
