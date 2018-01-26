/*
 outline_new_dialog.h     MindForger thinking notebook

 Copyright (C) 2016-2018 Martin Dvorak <martin.dvorak@mindforger.com>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef M8RUI_OUTLINE_NEW_DIALOG_H
#define M8RUI_OUTLINE_NEW_DIALOG_H

#include <QtWidgets>

#include "lib/src/model/tag.h"
#include "lib/src/model/outline_type.h"
#include "lib/src/mind/ontology/ontology_vocabulary.h"
#include "lib/src/mind/ontology/ontology.h"
#include "lib/src/model/stencil.h"
#include "lib/src/gear/string_utils.h"
#include "../widgets/edit_tags_panel.h"

#include "src/qt/model_meta_definitions.h"

class QDialogButtonBox;
class QTabWidget;

namespace m8r {

class OutlineNewDialog : public QDialog
{
    Q_OBJECT

    class GeneralTab;
    class AdvancedTab;

private:
    Ontology& ontology;

    GeneralTab* generalTab;
    AdvancedTab* advancedTab;

    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;

public:
    explicit OutlineNewDialog(
            const QString& memoryDirPath,
            Ontology& ontology,
            std::vector<Stencil*>& stencils,
            QWidget* parent);
    OutlineNewDialog(const OutlineNewDialog&) = delete;
    OutlineNewDialog(const OutlineNewDialog&&) = delete;
    OutlineNewDialog &operator=(const OutlineNewDialog&) = delete;
    OutlineNewDialog &operator=(const OutlineNewDialog&&) = delete;
    ~OutlineNewDialog();

    QString getOutlineName() const;
    Stencil* getStencil() const;
    const OutlineType* getOutlineType() const;
    int8_t getImportance() const;
    int8_t getUrgency() const;
    int getProgress() const;
    const std::vector<const Tag*>* getTags() const;

    void show();

private slots:
    void refreshPath(const QString &);
};



class OutlineNewDialog::GeneralTab : public QWidget
{
    Q_OBJECT

private:
    Ontology& ontology;

    QLabel* nameLabel;
    QLineEdit* nameEdit;
    QLabel* typeLabel;
    QComboBox* typeCombo;
    QLabel* importanceLabel;
    QComboBox* importanceCombo;
    QLabel* urgencyLabel;
    QComboBox* urgencyCombo;
    QLabel* progressLabel;
    QSpinBox* progressSpin;
    QLabel* stencilLabel;
    QComboBox* stencilCombo;

    EditTagsPanel* editTagsGroup;

public:
    explicit GeneralTab(Ontology& ontology, QWidget *parent);
    ~GeneralTab();

    QLineEdit* getNameEdit() const { return nameEdit; }
    QComboBox* getTypeCombo() const { return typeCombo; }
    QComboBox* getImportanceCombo() const { return importanceCombo; }
    QComboBox* getUrgencyCombo() const { return urgencyCombo; }
    QComboBox* getStencilCombo() const { return stencilCombo; }
    QSpinBox* getProgressSpin() const { return progressSpin; }
    const std::vector<const Tag*>* getTags() { return editTagsGroup->getTags(); }

    void clean();
};



class OutlineNewDialog::AdvancedTab : public QWidget
{
    Q_OBJECT

private:
    QLabel *pathLabel;
    QLabel *pathEdit;

private:
    const QString memoryDirPath;

public:
    explicit AdvancedTab(const QString& memoryDirPath, QWidget *parent);
    void refreshPath(const QString &name);
    ~AdvancedTab();
};

}
#endif // M8RUI_OUTLINE_NEW_DIALOG_H
