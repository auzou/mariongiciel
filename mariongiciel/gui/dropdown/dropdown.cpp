#include "dropdown.h"

/********************MULTI-SELECT-DROP-DOWN********************/

/**CONSTRUCTOR/DESCTRUCTOR**/


mariongiciel::gui::MultiSelectDropDown::MultiSelectDropDown(const int maxSelect,
                                                            const QIcon &removeIcon,
                                                            DropDown *dropDown,
                                                            QWidget *parent)
    : QWidget(parent),
      maxSelect(maxSelect),
      removeIcon(removeIcon),
      mainLayout(new QVBoxLayout(this)),
      dropDown(dropDown)
{
    this->setObjectName("multi-dropdown");
    this->dropDown->setParent(this);
    this->mainLayout->addWidget(dropDown, 0, Qt::AlignTop);
    this->setLayout(this->mainLayout);
    QObject::connect(this->dropDown, &DropDown::textChanged, this, &MultiSelectDropDown::addSelection);
}

mariongiciel::gui::MultiSelectDropDown::~MultiSelectDropDown() noexcept
{

}

/**PRIVATE-METHOD**/
void mariongiciel::gui::MultiSelectDropDown::addCustomWidget(const QString &text)
{
    QWidget *customWidget = new QWidget(this);
    QHBoxLayout *customWidgetLayout = new QHBoxLayout(customWidget);

    QPushButton *textButton = new QPushButton(text, customWidget);
    textButton->setEnabled(false);
    textButton->setMaximumWidth(QFontMetrics(QFont("Times")).horizontalAdvance(text));

    QPushButton *removeButton = new QPushButton(customWidget);
    removeButton->setIcon(this->removeIcon);
    removeButton->setMaximumWidth(64);

    customWidgetLayout->addWidget(textButton);
    customWidgetLayout->addWidget(removeButton);

    customWidget->setLayout(customWidgetLayout);

    this->mainLayout->addWidget(customWidget, 0, Qt::AlignTop);

    this->selection.push_back(qMakePair(text, customWidget));

    QObject::connect(removeButton, &QPushButton::clicked, this, &MultiSelectDropDown::removeSelection);
}

/**PUBLIC-METHOD**/
QStringList mariongiciel::gui::MultiSelectDropDown::getSelection() const
{
    return [this]()->QStringList {
        QStringList rData = QStringList();
        for(auto &i : this->selection)
        {
            rData.push_back(i.first);
        }
        return rData;
    }();
}

/**PRIVATE-SLOTS**/
void mariongiciel::gui::MultiSelectDropDown::addSelection(const QString &text)
{
    if(selection.size() >= this->maxSelect)
    {
        return;
    }
    for(auto &i : this->selection)
    {
        if(i.first == text)
        {
            return;
        }
    }
    this->addCustomWidget(text);
    emit selectChanged(this->getSelection());
}

void mariongiciel::gui::MultiSelectDropDown::removeSelection()
{
    QPushButton *senderButton = qobject_cast<QPushButton *>(sender());
    for(int i = 0; i < this->selection.size(); i++)
    {
        if(senderButton->parent() == this->selection[i].second)
        {
            this->mainLayout->removeWidget(this->selection[i].second);
            this->selection[i].second->deleteLater();
            this->selection.remove(i);
            emit selectChanged(this->getSelection());
            return;
        }
    }
}


/********************DROP-DOWN********************/

/**CONSTRUCTOR/DESCTRUCTOR**/

mariongiciel::gui::DropDown::DropDown(const QIcon &actionIcon, const QStringList &list, QWidget *parent)
    : QWidget(parent),
      customLineEdit(new CustomLineEdit(list, this))
{
    QVBoxLayout *dropDownLayout = new QVBoxLayout(this);
    this->setObjectName("dropdown");
    QAction *button = new QAction(this);
    button->setIcon(QIcon(actionIcon));
    this->customLineEdit->addAction(button, QLineEdit::LeadingPosition);

    this->customLineEdit->setClearButtonEnabled(true);

    this->customLineEdit->setPlaceholderText("Recherche");

    dropDownLayout->addWidget(this->customLineEdit, 0, Qt::AlignTop);

    this->setStyleSheet("QLineEdit {"
                                        "border: 2px solid gray;"
                                        "border-radius: 15px;"
                                        "padding: 6px;"
                                        "selection-background-color: darkgray;"
                                        "min-width: 10em;"
                                        "font: 20px;"
                                        "width:100%;"
                                     "}");

    this->setLayout(dropDownLayout);

    QObject::connect(this->customLineEdit, &CustomLineEdit::currentTextActivated, [this](const QString &text)->void {
        emit textChanged(text);
    });
}

mariongiciel::gui::DropDown::~DropDown() noexcept
{

}




/********************CUSTOM-LINE-EDIT********************/

/**CONSTRUCTOR/DESCTRUCTOR**/

mariongiciel::gui::CustomLineEdit::CustomLineEdit(const QStringList &list, QWidget *parent)
    : QLineEdit(parent)
{
    QCompleter *completer = new QCompleter(list, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    QPalette pal = completer->popup()->palette();
    pal.setBrush(QPalette::Base, Qt::transparent);
    completer->popup()->setPalette(pal);
    completer->popup()->setStyleSheet(
                                      "QAbstractItemView {"
                                        "selection-background-color: darkgray;"
                                        "border: 2px solid rgb(81, 81, 81);"
                                        "padding: 1px;"
                                        "border-radius: 15px;"
                                      "}"
                                      "QAbstractItemView::item {"
                                        "padding-top: 2px;"
                                        "padding-bottom: 2px;"
                                        "border-radius: 15px;"
                                      "}");

    this->setCompleter(completer);

    QObject::connect(completer, QOverload<const QString &>::of(&QCompleter::activated),
        [this](const QString &text){ emit currentTextActivated(text);
    });
    QObject::connect(this, &QLineEdit::textChanged, [this]()->void {
        if(this->text().isEmpty())
        {
            emit currentTextActivated(QString());
        }
    });
}

void mariongiciel::gui::CustomLineEdit::mousePressEvent(QMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent)
    this->completer()->complete();
}

mariongiciel::gui::CustomLineEdit::~CustomLineEdit() noexcept
{

}

