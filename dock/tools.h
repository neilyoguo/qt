#ifndef TOOLS_H
#define TOOLS_H

#include<QIcon>
#include<QString>

static QIcon svgIcon(const QString& File)
{
    QIcon SvgIcon(File);
    SvgIcon.addPixmap(SvgIcon.pixmap(92));
    return SvgIcon;
}




#endif // TOOLS_H


