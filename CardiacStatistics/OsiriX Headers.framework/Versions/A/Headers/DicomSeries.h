/*=========================================================================
  Program:   OsiriX

  Copyright (c) OsiriX Team
  All rights reserved.
  Distributed under GNU - LGPL
  
  See http://www.osirix-viewer.com/copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.
=========================================================================*/


#import <Cocoa/Cocoa.h>

/** \brief  Core Data Entity for a Series */

@interface DicomSeries : NSManagedObject
{
	NSNumber	*dicomTime;
}

- (NSSet *)paths;
- (NSSet *)keyImages;
- (NSArray *)sortedImages;
- (NSDictionary *)dictionary;
- (NSComparisonResult)compareName:(DicomSeries*)series;
- (NSNumber *) noFilesExcludingMultiFrames;

@end
