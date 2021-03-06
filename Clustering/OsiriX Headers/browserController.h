/*=========================================================================
  Program:   OsiriX

  Copyright (c) OsiriX Team
  All rights reserved.
  Distributed under GNU - GPL
  
  See http://www.osirix-viewer.com/copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.
=========================================================================*/


#import <Cocoa/Cocoa.h>
/*
#import "DCMView.h"
#import "MyOutlineView.h"
#import "PreviewView.h"
#import "QueryController.h"
#import "AnonymizerWindowController.h"
*/

@class MPR2DController;
@class NSCFDate;
@class BurnerWindowController;
@class ViewerController;
@class BonjourPublisher;
@class BonjourBrowser;
@class AnonymizerWindowController;
@class QueryController;
@class LogWindowController;
@class PreviewView;
@class MyOutlineView;
@class DCMView;
@class DCMPix;
@class StructuredReportController;


enum RootTypes{PatientRootType, StudyRootType, RandomRootType};
enum simpleSearchType {PatientNameSearch, PatientIDSearch};
enum queueStatus{QueueHasData, QueueEmpty};

@interface BrowserController : NSWindowController//NSObject
{
	NSManagedObjectModel			*managedObjectModel;
    NSManagedObjectContext			*managedObjectContext;
	
	NSString				*currentDatabasePath;
	BOOL					isCurrentDatabaseBonjour;
	NSString				*transferSyntax;
    NSArray                 *dirArray;
    NSToolbar               *toolbar;
	
	NSMutableArray			*sendQueue;
	NSMutableDictionary		*bonjourReportFilesToCheck;
	
    NSMutableArray          *previewPix, *previewPixThumbnails;
	
	NSMutableArray			*draggedItems;
		
	NSMutableDictionary		*activeSends;
	NSMutableArray			*sendLog;
	NSMutableDictionary		*activeReceives;
	NSMutableArray			*receiveLog;
	
	QueryController * queryController;
	AnonymizerWindowController *anonymizerController;
	BurnerWindowController *burnerWindowController;
	LogWindowController *logWindowController;
	
	NSNumberFormatter		*numFmt;
    
    DCMPix                  *curPreviewPix;
    
    NSTimer                 *timer, *IncomingTimer, *matrixDisplayIcons, *refreshTimer, *databaseCleanerTimer, *bonjourTimer, *bonjourRunLoopTimer, *deleteQueueTimer;
	long					loadPreviewIndex, previousNoOfFiles;
	NSManagedObject			*previousItem;
    
	long					previousBonjourIndex;
	
    long                    COLUMN;
	IBOutlet NSSplitView	*splitViewHorz, *splitViewVert;
    
	BOOL					setDCMDone, mountedVolume, needDBRefresh;
	
	NSMutableArray			*albumNoOfStudiesCache;
	
    volatile BOOL           shouldDie, threadRunning, threadWillRunning, bonjourDownloading;
	
	NSArray							*outlineViewArray, *originalOutlineViewArray;
	NSArray							*matrixViewArray;
	NSArray							*allColumns;
	
	NSString						*_searchString;
	
	IBOutlet NSTextField			*databaseDescription;
	IBOutlet MyOutlineView          *databaseOutline;
	IBOutlet NSMatrix               *oMatrix;
	IBOutlet NSTableView			*albumTable;
	IBOutlet NSSegmentedControl		*segmentedAlbumButton;
	
	IBOutlet NSSplitView			*sourcesSplitView;
	IBOutlet NSBox					*bonjourSourcesBox;
	
	IBOutlet NSTextField			*bonjourServiceName, *bonjourPassword;
	IBOutlet NSTableView			*bonjourServicesList;
	IBOutlet NSButton				*bonjourSharingCheck, *bonjourPasswordCheck;
	BonjourPublisher				*bonjourPublisher;
	BonjourBrowser					*bonjourBrowser;
	
	IBOutlet NSSlider				*animationSlider;
	IBOutlet NSButton				*animationCheck;
    
    IBOutlet PreviewView			*imageView;
	
	IBOutlet NSWindow				*subSeriesWindow;
	IBOutlet NSButton				*subSeriesInterval, *subSeriesOKButton;
	IBOutlet NSTextField			*subSeriesFrom, *subSeriesTo, *subSeriesIntervalText, *memoryMessage;
	IBOutlet NSSlider				*subSeriesSlider;
	IBOutlet NSBox					*enoughMem, *notEnoughMem;
	
	IBOutlet NSWindow				*bonjourPasswordWindow;
	IBOutlet NSTextField			*password;
	
	IBOutlet NSWindow				*newAlbum;
	IBOutlet NSTextField			*newAlbumName;
	
	IBOutlet NSWindow				*editSmartAlbum;
	IBOutlet NSTextField			*editSmartAlbumName, *editSmartAlbumQuery;
	
	IBOutlet NSDrawer				*albumDrawer;
	
	IBOutlet NSWindow				*rebuildWindow;
	IBOutlet NSMatrix				*rebuildType;
	IBOutlet NSTextField			*estimatedTime, *noOfFilesToRebuild, *warning;
	
	IBOutlet NSWindow				*customTimeIntervalWindow;
	IBOutlet NSDatePicker			*customStart, *customEnd, *customStart2, *customEnd2;
	IBOutlet NSView					*timeIntervalView;
	int								timeIntervalType;
	NSDate							*timeIntervalStart, * timeIntervalEnd;
	
	IBOutlet NSView					*searchView;
	IBOutlet NSSearchField			*searchField;
	NSToolbarItem					*toolbarSearchItem;
	int								searchType;
	
	IBOutlet NSWindow				*mainWindow;
	IBOutlet NSMenu					*imageTileMenu;
	IBOutlet NSWindow				*urlWindow;
	IBOutlet NSTextField			*urlString;
	
//	IBOutlet NSTableView			*sendLogTable;
	
	IBOutlet NSForm					*rdPatientForm;
	IBOutlet NSForm					*rdPixelForm;
	IBOutlet NSForm					*rdVoxelForm;
	IBOutlet NSForm					*rdOffsetForm;
	IBOutlet NSMatrix				*rdPixelTypeMatrix;
	IBOutlet NSView					*rdAccessory;
	
//	IBOutlet NSMatrix				*keyImageMatrix;
	IBOutlet NSView					*exportAccessoryView;
	IBOutlet NSButton				*addDICOMDIRButton;
    
	NSLock							*checkIncomingLock;
	NSTimeInterval					lastSaved;
	
    BOOL							showAllImages, DatabaseIsEdited, isNetworkLogsActive;
	NSConditionLock					*queueLock;
	
	IBOutlet NSScrollView			*thumbnailsScrollView;
	
	NSPredicate						*_fetchPredicate;
	NSPredicate						*_filterPredicate;
	NSString						*_filterPredicateDescription;
	
	NSString						*fixedDocumentsDirectory;
	
	char							cfixedDocumentsDirectory[ 1024];
	
	NSTimeInterval					databaseLastModification;
	
	StructuredReportController		*structuredReportController;
	
	NSMutableArray					*deleteQueueArray;
	NSLock							*deleteQueue, *deleteInProgress;
	
	IBOutlet NSProgressIndicator	*incomingProgress;
}

+ (BrowserController*) currentBrowser;

- (void) emptyDeleteQueueThread;
- (void) emptyDeleteQueue:(id) sender;
- (void) addFileToDeleteQueue:(NSString*) file;
- (NSString*) getNewFileDatabasePath: (NSString*) extension;
- (NSManagedObjectModel *)managedObjectModel;
- (NSManagedObjectContext *)managedObjectContext;
- (NSArray*) childrenArray: (NSManagedObject*) item;
- (NSArray*) imagesArray: (NSManagedObject*) item;
- (NSArray*) imagesArray: (NSManagedObject*) item anyObjectIfPossible: (BOOL) any;
- (NSManagedObjectContext *) managedObjectContextLoadIfNecessary:(BOOL) loadIfNecessary;
- (void) setNetworkLogs;
- (BOOL) isNetworkLogsActive;
- (NSTimeInterval) databaseLastModification;
- (IBAction) matrixDoublePressed:(id)sender;
- (void) addURLToDatabaseEnd:(id) sender;
- (void) addURLToDatabase:(id) sender;
- (NSArray*) addURLToDatabaseFiles:(NSArray*) URLs;
-(BOOL) findAndSelectFile: (NSString*) path image: (NSManagedObject*) curImage shouldExpand: (BOOL) expand;
- (IBAction) sendiDisk:(id) sender;
- (IBAction) sendiPod:(id) sender;
- (void) selectServer: (NSArray*) files;
- (void) loadDICOMFromiPod;
- (long) saveDatabase:(NSString*) path;
- (void) addDICOMDIR:(NSString*) dicomdir :(NSMutableArray*) files;
-(NSMutableArray*) copyFilesIntoDatabaseIfNeeded:(NSMutableArray*) filesInput;
-(void) loadSeries :(NSManagedObject *)curFile :(ViewerController*) viewer :(BOOL) firstViewer keyImagesOnly:(BOOL) keyImages;
-(void) loadNextPatient:(NSManagedObject *) curImage :(long) direction :(ViewerController*) viewer :(BOOL) firstViewer keyImagesOnly:(BOOL) keyImages;
-(void) loadNextSeries:(NSManagedObject *) curImage :(long) direction :(ViewerController*) viewer :(BOOL) firstViewer keyImagesOnly:(BOOL) keyImages;
- (void) openViewerFromImages:(NSArray*) toOpenArray movie:(BOOL) movieViewer viewer:(ViewerController*) viewer keyImagesOnly:(BOOL) keyImages;
- (void) export2PACS:(id) sender;
- (void) queryDICOM:(id) sender;
-(void) exportQuicktimeInt:(NSArray*) dicomFiles2Export :(NSString*) path :(BOOL) html;
- (IBAction) delItem:(id) sender;
- (void) delItemMatrix: (NSManagedObject*) obj;
- (IBAction) selectFilesAndFoldersToAdd:(id) sender;
- (void) showDatabase:(id)sender;
-(IBAction) matrixPressed:(id)sender;
-(void) loadDatabase:(NSString*) path;

- (void) viewerDICOMInt:(BOOL) movieViewer dcmFile:(NSArray *)selectedLines viewer:(ViewerController*) viewer;
- (NSToolbarItem *) toolbar: (NSToolbar *)toolbar itemForItemIdentifier: (NSString *) itemIdent willBeInsertedIntoToolbar:(BOOL) willBeInserted;
- (NSArray *)toolbarDefaultItemIdentifiers:(NSToolbar*)toolbar;
- (NSArray *)toolbarAllowedItemIdentifiers:(NSToolbar*)toolbar;
- (BOOL) validateToolbarItem: (NSToolbarItem *) toolbarItem;

- (void) setupToolbar;

- (IBAction)customize:(id)sender;
- (IBAction)showhide:(id)sender;

- (void) exportDICOMFile:(id) sender;
- (void) viewerDICOM:(id) sender;
- (void)newViewerDICOM:(id) sender;
- (void) viewerDICOMKeyImages:(id) sender;
- (void) viewerDICOMMergeSelection:(id) sender;
- (void) burnDICOM:(id) sender;
- (IBAction) anonymizeDICOM:(id) sender;
- (IBAction)addSmartAlbum: (id)sender;
- (IBAction)search: (id)sender;
- (IBAction)setSearchType: (id)sender;
- (IBAction)setImageTiling: (id)sender;

- (IBAction)setTimeIntervalType: (id)sender;
- (IBAction) endCustomInterval:(id) sender;
- (IBAction) customIntervalNow:(id) sender;

- (IBAction) openDatabase:(id) sender;
- (IBAction) createDatabase:(id) sender;
- (void) openDatabaseIn:(NSString*) a Bonjour:(BOOL) isBonjour;

- (IBAction) endReBuildDatabase:(id) sender;
- (IBAction) ReBuildDatabase:(id) sender;
- (IBAction) ReBuildDatabaseSheet: (id)sender;
- (long) COLUMN;
- (BOOL) is2DViewer;
- (void) previewSliderAction:(id) sender;
- (void) addHelpMenu;

- (BOOL) isItCD:(NSArray*) pathFilesComponent;
- (void)storeSCPComplete:(id)sender;
- (NSMutableArray *) filesForDatabaseOutlineSelection :(NSMutableArray*) correspondingDicomFile;
- (NSMutableArray *) filesForDatabaseMatrixSelection :(NSMutableArray*) correspondingManagedObjects;

- (void) resetListenerTimer;
- (IBAction) smartAlbumHelpButton:(id) sender;

- (NSArray*) addFilesToDatabase:(NSArray*) newFilesArray;
- (NSArray*) addFilesAndFolderToDatabase:(NSArray*) filenames;
-(NSArray*) addFilesToDatabase:(NSArray*) newFilesArray onlyDICOM:(BOOL) onlyDICOM safeRebuild:(BOOL) safeProcess produceAddedFiles:(BOOL) produceAddedFiles;

//- (short) createAnonymizedFile:(NSString*) srcFile :(NSString*) dstFile;

- (void)runSendQueue:(id)object;
- (void)addToQueue:(NSArray *)array;
- (MyOutlineView*) databaseOutline;

-(void) previewPerformAnimation:(id) sender;
-(void) matrixDisplayIcons:(id) sender;

//- (void)reloadSendLog:(id)sender;
- (IBAction)importRawData:(id)sender;
- (void) setBurnerWindowControllerToNIL;

- (void) refreshColumns;
- (void) outlineViewRefresh;
- (void) matrixInit:(long) noOfImages;
- (IBAction) albumButtons: (id)sender;
- (NSArray*) albumArray;
- (void) refreshSmartAlbums;

- (NSArray*) imagesPathArray: (NSManagedObject*) item;

- (void) autoCleanDatabaseFreeSpace:(id) sender;
- (void) autoCleanDatabaseDate:(id) sender;

- (void) refreshDatabase:(id) sender;

- (void) removeAllMounted;
- (NSTableView*) albumTable;

//bonjour
- (void) setBonjourDatabaseValue:(NSManagedObject*) obj value:(id) value forKey:(NSString*) key;
- (BOOL) isCurrentDatabaseBonjour;
- (void)setServiceName:(NSString*) title;
- (IBAction)toggleBonjourSharing:(id) sender;
- (void) setBonjourSharingEnabled:(BOOL) boo;
- (void) bonjourWillPublish;
- (void) bonjourDidStop;
- (IBAction) bonjourServiceClicked:(id)sender;
- (NSString*) currentDatabasePath;
- (void) setBonjourDownloading:(BOOL) v;
- (NSString*) getLocalDCMPath: (NSManagedObject*) obj :(long) no;
- (void) displayBonjourServices;
- (NSString*) localDatabasePath;
- (NSString*) askPassword;
- (NSString*) bonjourPassword;
- (long) currentBonjourService;
- (void) resetToLocalDatabase;
- (void) createContextualMenu;
- (NSBox*) bonjourSourcesBox;
- (NSTextField*) bonjourServiceName;
- (NSTextField*) bonjourPasswordTextField;
- (NSButton*) bonjourSharingCheck;
- (NSButton*) bonjourPasswordCheck;
- (void) bonjourRunLoop:(id) sender;
- (void) checkIncomingThread:(id) sender;
- (NSArray*) openSubSeries: (NSArray*) toOpenArray;
- (IBAction) checkMemory:(id) sender;

//DB plugins
- (void)executeFilterDB:(id)sender;

- (NSString *)documentsDirectory;
- (NSString *) fixedDocumentsDirectory;
- (char *) cfixedDocumentsDirectory;
- (NSString *) setFixedDocumentsDirectory;
- (IBAction)showLogWindow: (id)sender ;

- (NSString *)folderPathResolvingAliasAndSymLink:(NSString *)path;

- (NSString *)searchString;
- (void)setSearchString:(NSString *)searchString;
- (NSPredicate*)fetchPredicate;
- (void)setFetchPredicate:(NSPredicate *)predicate;
- (NSPredicate*)filterPredicate;
- (NSString*) filterPredicateDescription;
- (void)setFilterPredicate:(NSPredicate *)predicate description:(NSString*) desc;
- (NSPredicate *)createFilterPredicate;
- (NSString *)createFilterDescription;

- (IBAction) generateReport: (id) sender;
- (IBAction) deleteReport: (id) sender;
- (IBAction)srReports: (id)sender;



- (NSArray *)databaseSelection;
- (IBAction)databaseWindow:(id)sender;

/******Notifactions posted by browserController***********

@"NewStudySelectedNotification" with userinfo key @"Selected Study" posted when a newStudy is selected in the browser
@"Close All Viewers" posted when close open windows if option key pressed.	
@"DCMImageTilingHasChanged" when image tiling has changed
OsirixAddToDBNotification posted when files are added to the DB

*/


@end
