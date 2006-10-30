/***************************************************************************
                          kmmtracksoundpanel.h  -  description
                             -------------------
    begin                : Tue Apr 9 2002
    copyright            : (C) 2002 by Jason Wood
    email                : jasonwood@blueyonder.co.uk
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KMMTRACKSOUNDPANEL_H
#define KMMTRACKSOUNDPANEL_H


#include <qlabel.h>
#include <qhbox.h>
#include <qpixmap.h>
#include <qlayout.h>

#include "trackheader_ui.h"
#include "doctracksound.h"
#include "kmmtrackpanel.h"

class KdenliveDoc;

namespace Gui {
    class KdenliveApp;
    class KTimeLine;

/**KMMTrackSoundPanel is the Track panel for sound files.
It contains several functions that can be used to manipulate
the main sound widget in different ways.
  *@author Jason Wood
  */

    class KMMTrackSoundPanel:public KMMTrackPanel {
      Q_OBJECT public:
	KMMTrackSoundPanel(KdenliveApp * app,
	    KTimeLine * timeline,
	    KdenliveDoc * document,
	    DocTrackSound * docTrack,
	    bool isCollapsed, QWidget * parent = 0, const char *name = 0);
	~KMMTrackSoundPanel();

	virtual void setSelected(bool isSelected);

	private slots:
        void resizeTrack();
	void decorateTrack();
        void muteTrack();

      private:			// Public attributes
  /**  */
	 TrackHeader m_trackHeader;
         bool m_mute;
         
      signals: 
           void collapseTrack(KTrackPanel *, bool);
    };

}				// namespace Gui
#endif
