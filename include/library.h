/*
 * library.h
 *
 *  Created on: Nov 22, 2011
 *      Author: stephan
 *
 *      Beschrijving:
 *      computer vision library voor gebruik in deze applicatie.
 *      Wat komt hierin:
 *      	een input bron ( camera of stille beelden)
 *      	Welke operaties er op de bron moeten worden uitgevoerd
 *      	output, en welke vorm deze moet zijn
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

/**
 * external library includes
 */
#include <opencv2/opencv.hpp>
#include <string>
#include <new>
#include <cmath>
#include <vector>
#include <boost/thread/thread.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/mutex.hpp>

/*------------------------------*/

/**
 * local header includes
 */
#include "input.h"
#include "resource.h"
#include "gui.h"
#include "algorithms.h"


/*------------------------------*/

/**
 * globale variabelen en defines
 */



#endif /* LIBRARY_H_ */
