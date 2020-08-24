#include "internalstyle.h"
#include <QApplication>
#include <QDebug>

InternalStyle::InternalStyle()
{
//    double transparency;
    if(QGSettings::isSchemaInstalled(QString("org.ukui.control-center.personalise").toLocal8Bit()))
    {
        QGSettings* gsetting=new QGSettings(QString("org.ukui.control-center.personalise").toLocal8Bit());
//        if(gsetting->keys().contains(QString("transparency")))
//        {
//            transparency=gsetting->get("transparency").toDouble();
//        }

        connect(gsetting,&QGSettings::changed,[=](const QString &key){
            qDebug()<<gsetting->get("transparency").toDouble();
//            standardPalette();
//            for (auto widget : QApplication::allWidgets()) {
//                widget->update();
//            }

        });
    }
}

QPalette InternalStyle::standardPalette() const
{
    auto m_palette=QProxyStyle::standardPalette();
    QColor m_windowbg,m_highlightbg,m_textbg,m_base;
    if(QGSettings::isSchemaInstalled(QString("org.ukui.style").toLocal8Bit()))
    {
        QGSettings* gsetting=new QGSettings(QString("org.ukui.style").toLocal8Bit());
        if(gsetting->keys().contains(QString("styleName")))
        {
            if(gsetting->get("style-name").toString()=="ukui-default")
            {
                m_windowbg=QColor(222, 222, 222);
                m_highlightbg=QColor(0, 0, 0);
                m_highlightbg.setAlphaF(0.15);
                m_textbg=QColor(0, 0, 0);
                m_textbg.setAlphaF(0.85);
                m_base=QColor(255,255,255);
                m_base.setAlphaF(0.15);

            }
            else if(gsetting->get("style-name").toString()=="ukui-dark")
            {
                m_windowbg=QColor(19, 19, 20);
                m_highlightbg=QColor(255,255,255);
                m_highlightbg.setAlphaF(0.14);
                m_textbg=QColor(255, 255, 255);
                m_textbg.setAlphaF(0.97);
                m_base=QColor(255,255,255);
                m_base.setAlphaF(0.06);
            }
        }
        m_palette.setBrush(QPalette::Window,m_windowbg);
        m_palette.setBrush(QPalette::Highlight,m_highlightbg);
        m_palette.setBrush(QPalette::Text,m_textbg);
        m_palette.setBrush(QPalette::Base,m_base);
        return m_palette;
    }
    return m_palette;
}

//void InternalStyle::drawPrimitive(QStyle::PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
//{

//    double transparency;
//    if(QGSettings::isSchemaInstalled(QString("org.ukui.control-center.personalise").toLocal8Bit()))
//        {
//            QGSettings* gsetting=new QGSettings(QString("org.ukui.control-center.personalise").toLocal8Bit());
//            if(gsetting->keys().contains(QString("transparency")))
//            {
//                transparency=gsetting->get("transparency").toDouble();
//            }
//    }
////    qDebug()<<transparency;
//    switch (element) {
//    case QStyle::PE_Frame:
//    {
//        QStyleOptionFrame frame=*qstyleoption_cast<const QStyleOptionFrame*>(option);
//        QFrame::Shape shape=frame.frameShape;
//        switch (shape) {
//        case QFrame::StyledPanel:
//        {
//            painter->save();
//            painter->setRenderHint(QPainter::Antialiasing);
//            painter->setPen(Qt::transparent);
//            painter->setBrush(option->palette.color(QPalette::Window));
//            painter->setOpacity(0.7);
//            painter->drawRoundedRect(option->rect,6,6);
//            painter->restore();
//            break;
//        }
//        case QFrame::VLine:
//        {
////            painter->save();
////            painter->setRenderHint(QPainter::Antialiasing);
////            painter->setPen(Qt::transparent);
//////            painter->setBrush(option->palette.color(QPalette::Window));
//////            painter->setOpacity(0.7);
////            painter->setBrush(Qt::red);
////            painter->drawRoundedRect(option->rect,6,6);
////            painter->restore();

//            QPoint p1,p2;
//            p1 = QPoint(option->rect.x() + option->rect.width() / 2, option->rect.y());
//            p2 = QPoint(p1.x(), p1.y() + option->rect.height());
//            painter->save();
//            painter->setPen(Qt::red);
//            painter->drawLine(p1,p2);
//            painter->restore();
//            break;
//        }
//        default:
//            break;
//        }

//    }
//        break;

//    default:
//        break;
//    }

//    QProxyStyle::drawPrimitive(element, option, painter, widget);
//}

void InternalStyle::drawControl(QStyle::ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    double transparency;
    if(QGSettings::isSchemaInstalled(QString("org.ukui.control-center.personalise").toLocal8Bit()))
        {
            QGSettings* gsetting=new QGSettings(QString("org.ukui.control-center.personalise").toLocal8Bit());
            if(gsetting->keys().contains(QString("transparency")))
            {
                transparency=gsetting->get("transparency").toDouble();
            }
    }
    switch (element) {
    case QStyle::CE_ShapedFrame:
    {
        const QStyleOptionFrame *frame=qstyleoption_cast<const QStyleOptionFrame*>(option);
        QFrame::Shape shape=frame->frameShape;
        switch (shape) {
        case QFrame::StyledPanel: {
            painter->save();
            painter->setRenderHint(QPainter::Antialiasing);
            painter->setPen(Qt::transparent);
            painter->setBrush(option->palette.color(QPalette::Window));
            painter->setOpacity(0.7);
            painter->drawRoundedRect(option->rect,6,6);
            painter->restore();
            return;
        }

        case QFrame::VLine: {
            QPoint p1,p2;
            p1 = QPoint(option->rect.x() + option->rect.width() / 2, option->rect.y());
            p2 = QPoint(p1.x(), p1.y() + option->rect.height());
            painter->save();
            painter->setPen(option->palette.color(QPalette::Base));
//            painter->drawRect(option->rect);
            painter->drawLine(p1,p2);
            painter->restore();
            return;
        }

        default:
            break;
        }

    }

    default:
        break;
    }

    return QProxyStyle::drawControl(element, option, painter, widget);
}

void InternalStyle::polish(QPalette &pal)
{
    pal=standardPalette();
//    QProxyStyle::polish(pal);
}

//void InternalStyle::polish(QWidget *widget)
//{
//    QProxyStyle::polish(widget);
//    if (qobject_cast<QFrame *>(widget)) {
//        auto pal = standardPalette();
//        //pal.setColor(QPalette::Window, pal.base().color());
//        widget->setPalette(pal);
//    }
//}
