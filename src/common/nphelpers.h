#ifndef NPHELPERS_H
#define NPHELPERS_H

#include <QQuickTextDocument>
#include <theme.h>

namespace Npanda
{
    namespace common
    {
        extern QQuickTextDocument *doc;
        extern KSyntaxHighlighting::Theme shTheme;
    } // namespace common

} // namespace Npanda

using namespace Npanda::common;

#endif // NPHELPERS_H
