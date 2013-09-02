//
//  ViewController.m
//  sketchometry
//
//  Created by Heiko Vogel on 17.01.13.
//  Copyright (c) 2013 DMI. All rights reserved.
//

#import "ViewController.h"

#define skmDirectory @"skm/GUI" // @"rel" //  

#define portrait @"Default-Portrait@2x~ipad.png"
#define landscape @"Default-Landscape@2x~ipad.png"

#define folderBeginMarker @"FOLDER_"
#define folderEndMarker @"_REDLOF"

enum {
    NOT_IN_FOLDER,
    IS_FOLDER,
    IS_FILE
};

@interface ViewController ()
@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [splash setHidden:TRUE];
    [webview setHidden:TRUE];
    
    [splash setBackgroundColor:[UIColor colorWithRed:117.0/255.0 green:178.0/255.0 blue:211.0/255.0 alpha:0.84]];
    [splash setImage:[UIImage imageNamed:portrait]];
    
    if (self.interfaceOrientation == UIDeviceOrientationPortrait || self.interfaceOrientation == UIDeviceOrientationPortraitUpsideDown)
        [self didRotateFromInterfaceOrientation:UIInterfaceOrientationLandscapeLeft];
    else
        [self didRotateFromInterfaceOrientation:UIInterfaceOrientationPortrait];
    
    NSURL *url = [NSURL fileURLWithPath:[[NSBundle mainBundle] pathForResource:@"index" ofType:@"html" inDirectory:skmDirectory]];
    
    NSURLRequest *request = [NSURLRequest requestWithURL:url];
    
    [splash setHidden:FALSE];
    [act startAnimating];
    
    NSString *logString = @"logToAppleApp = function(msg) { var iframe = document.createElement('IFRAME'); iframe.setAttribute('src', '--> ' + msg + ':##logToApp##'); document.documentElement.appendChild(iframe); iframe.parentNode.removeChild(iframe); iframe = null; };";
    
    [webview stringByEvaluatingJavaScriptFromString:logString];
    
    [webview stringByEvaluatingJavaScriptFromString:@"console.assert = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.debug = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.error = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.info = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.log = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.warn = logToAppleApp;"];
    
    [webview stringByEvaluatingJavaScriptFromString:@"window.onerror = function(message, file, lineNumber) { " \
        "console.error(message); var error = file + ':' + lineNumber + ' <--'; console.error(error); return true; };"];
   
    // Load Sketchometry into the webview
    
    [webview loadRequest:request];
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
    if (fromInterfaceOrientation == UIInterfaceOrientationPortrait || fromInterfaceOrientation == UIInterfaceOrientationPortraitUpsideDown) {
        splash.contentMode = UIViewContentModeScaleAspectFit;
        [splash setImage:[UIImage imageNamed:landscape]];
    } else {
        splash.contentMode = UIViewContentModeScaleAspectFill;
        [splash setImage:[UIImage imageNamed:portrait]];
    }
}

- (void)dealloc
{
    [act release];
    [webview release];
    [splash release];
    
    if (document)
        [document release];
    
    if (idocs)
        [idocs release];
    
    if (iquery)
        [iquery release];
    
    if (currentFolder)
        [currentFolder release];
    
    [super dealloc];
}

/********* iCloud Query methods -- BEGIN *********/

- (NSMetadataQuery*)iDocsQuery
{
    NSString* filePattern;
    NSMetadataQuery* aQuery = [[NSMetadataQuery alloc] init];
    
    if (aQuery) {
        [aQuery setSearchScopes:[NSArray arrayWithObject:NSMetadataQueryUbiquitousDataScope]];
        filePattern = @"*"; // @"*.*"; // [NSString stringWithFormat:@"*.sketch"];
        [aQuery setPredicate:[NSPredicate predicateWithFormat:@"%K LIKE %@", NSMetadataItemFSNameKey, filePattern]];
    }
    
    return aQuery;
}

- (void)iDocsQueryHandler:(NSNotification*)aNotification
{
    NSNumber *aBool;
    NSInteger i, j;
    
    NSURL *fileURL;
    
    NSArray *queryResults;
    NSMetadataItem *result;
    
    [iquery disableUpdates];
    queryResults = [iquery results];
    
    [idocs removeAllObjects];
    
    j = [queryResults count];
    
    for (i=0; i<j; i++) {
        
        result = [queryResults objectAtIndex:i];
        fileURL = [result valueForAttribute:NSMetadataItemURLKey];
        aBool = nil;
        
        [fileURL getResourceValue:&aBool forKey:NSURLIsHiddenKey error:nil]; // no hidden files
        
        if (aBool && ![aBool boolValue])
            [idocs addObject:fileURL];
    }
    
    [iquery enableUpdates];
}

- (void)iDocsInit
{
    NSURL *iCloud = [[NSFileManager defaultManager] URLForUbiquityContainerIdentifier:nil];
    
    if (iCloud) {
        
        NSLog(@"Initializing iDocs ...");
        
        if (iquery) {
            [iquery release];
            [[NSNotificationCenter defaultCenter] removeObserver:self];
        }
        
        iquery = [self iDocsQuery];
        
        if (!idocs)
            idocs = [[NSMutableArray alloc] init];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(iDocsQueryHandler:) name:NSMetadataQueryDidFinishGatheringNotification object:nil];
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(iDocsQueryHandler:) name:NSMetadataQueryDidUpdateNotification object:nil];
        
        [iquery startQuery];
        
        currentFolder = [[NSString alloc] initWithString:@""];
        
        [webview stringByEvaluatingJavaScriptFromString:@"GUI.Export.iCloud.isAvailable = true;"];
    } else
        [webview stringByEvaluatingJavaScriptFromString:@"GUI.Export.iCloud.isAvailable = false;"];
}

/********* iCloud Query methods -- END *********/

/********* Helper methods -- BEGIN *********/

- (void)webviewMsg:(NSArray*)request
{
    NSString *action = [request[0] lastPathComponent];
    
    if ([action isEqualToString:@"1"]) {
        [self iCloudListFiles:request[1]];
    } else if ([action isEqualToString:@"2"]) {
        [self iCloudDownloadFile:request[1]];
    } else if ([action isEqualToString:@"3"]) {
        [self iCloudUploadFile:request[1] content:request[2] allowOverwrite:[request[3] isEqualToString:@"true"] omitCallback:FALSE];
    } else if ([action isEqualToString:@"4"]) {
        [self iCloudDeleteFile:request[1]];
    } else if ([action isEqualToString:@"5"]) {
        [self iCloudCreateFolder:request[1]];
    } else
        NSLog(@"Unknown webView request: %@", request[0]);
}

- (NSURL*)documentURL:(NSString*)documentName
{
    NSFileManager *fm = [NSFileManager defaultManager];
    NSURL *documentURL = [fm URLForUbiquityContainerIdentifier:nil];
    
    if (![currentFolder isEqualToString:@""])
        documentURL = [documentURL URLByAppendingPathComponent:currentFolder];
    
    if (![documentName isEqualToString:@""])
        documentURL = [NSURL URLWithString:[[documentURL absoluteString] stringByAppendingString:documentName]];
    
    return documentURL;
}

- (NSInteger)countSubstrings:(NSString*)patientString substring:(NSString*)substring
{
    NSRange range;
    NSString *check;
    
    NSInteger i, j, k = 0;
    
    j = patientString.length - substring.length;
    
    for (i=0; i<=j; i++) {
        range = NSMakeRange(i, substring.length);
        check = [patientString substringWithRange:range];
        
        if ([substring isEqualToString:check]) {
            i = i + substring.length - 1; // -1: remember the i++ in the loop ...
            k++;
        }
    }
    
    return k;
}

- (NSString*)keepFolderPathOccurences:(NSString*)name ocurrences:(NSInteger)ocurrences
{
    NSRange range;
    NSString *check;
    
    NSInteger i, j, k = 0;
 
    j = name.length - folderEndMarker.length;
    
    for (i=0; i<j; i++) {
        range = NSMakeRange(i, folderEndMarker.length);
        check = [name substringWithRange:range];
        
        if ([folderEndMarker isEqualToString:check])
            k++;
        
        if (k == ocurrences)
            return [name substringWithRange:NSMakeRange(0, i + folderEndMarker.length)];
    }
    
    return name;
}

- (NSString*)examinePathName:(NSString*)name folderCount:(NSInteger*)folderCount status:(NSInteger*)status
{
    BOOL isFolder;
    NSRange range;
    
    range = NSMakeRange(0, currentFolder.length);
    
    if ([name length] < [currentFolder length ]
        || ![[name substringWithRange:range] isEqualToString:currentFolder]) {
        
        *status = NOT_IN_FOLDER;
        return name;
    }
    
    // Remove currentFolder from the beginning of name
    
    name = [name stringByReplacingOccurrencesOfString:currentFolder withString:@"" options:NSLiteralSearch range:range];
    
    if ([name length] == 0) {
        *status = NOT_IN_FOLDER;
        return name;
    }
    
    // Count the number of folderEndMarkers
    
    *folderCount = [self countSubstrings:name substring:folderEndMarker];
    
    if (*folderCount > 1) {
        *status = NOT_IN_FOLDER;
        return name;
    }
    
    // Check the end of name for a folderEndMarker and remove the marker pair ...
    
    if (*folderCount == 1) {
        
        range = NSMakeRange(name.length - folderEndMarker.length, folderEndMarker.length);
        
        // Check if name belongs to a file in a sub-folder (one hierarchy lower)
        
        if (![[name substringWithRange:range] isEqualToString:folderEndMarker]) {
            
            *status = NOT_IN_FOLDER;
            return name;
        }
        
        name = [name stringByReplacingOccurrencesOfString:folderBeginMarker withString:@""];
        name = [name stringByReplacingOccurrencesOfString:folderEndMarker withString:@""];
        
        isFolder = TRUE;
    } else
        isFolder = FALSE;
    
    *status = (isFolder) ? IS_FOLDER : IS_FILE;
    
    return name;
}

/********* Helper methods -- END *********/

/********* List / Load / Save / Delete / Create -- BEGIN *********/

- (void)iCloudListFiles:(NSString*)folder
{
    BOOL isFolder;
    
    NSInteger i, j, k = 0;
    NSInteger status, currentFolderCount, folderCount;

    NSRegularExpression *regex;
    NSString *name, *nid, *sep, *listString, *tmpString;
    
    if ([folder isEqualToString:@"/"]) {
        
        // Requesting root directory listing ...
        
        [currentFolder release];
        currentFolder = [[NSString alloc] initWithString:@""];
        
        folder = @"";
        
    } else {
      
        // Extract the folder's hierarchy level ...
        
        regex = [NSRegularExpression regularExpressionWithPattern:@"/.*" options:0 error:nil];
        folderCount = [[regex stringByReplacingMatchesInString:folder options:0 range:NSMakeRange(0, [folder length]) withTemplate:@""] integerValue];
        
        // Determine the current folder's hierarchy level ...
        
        currentFolderCount = [self countSubstrings:currentFolder substring:folderEndMarker];

        NSLog(@"folderCount %d, currentFolderCount %d", folderCount, currentFolderCount);

        
        if (folderCount < currentFolderCount) { // Go to (a) parent directory ...
            
            tmpString = [[self keepFolderPathOccurences:currentFolder ocurrences:folderCount] retain];
            
            [currentFolder release];
            currentFolder = tmpString;

            folder = @"";
            
        } else if (folderCount == currentFolderCount) { // Refresh the current directory ...
            
            folder = @"";
            
        } else { // Descend in the directory hierarchy ...
            
            regex = [NSRegularExpression regularExpressionWithPattern:@".*/" options:0 error:nil];
            folder = [regex stringByReplacingMatchesInString:folder options:0 range:NSMakeRange(0, [folder length]) withTemplate:@""];
        }
    }
    
    j = [idocs count];
    
    if (![folder isEqualToString:@""] && ![folder isEqualToString:@"."]) {
        
        name = [[self documentURL:[NSString stringWithFormat:@"%@%@%@", folderBeginMarker, folder, folderEndMarker]] absoluteString];
        
        for (i=0; i<j; i++)
            if ([[[idocs objectAtIndex:i] absoluteString] isEqualToString:name])
                break;
        
        if (i >= j)
            return;
        
        tmpString = currentFolder;
        currentFolder = [[NSString alloc] initWithFormat:@"%@%@%@%@", tmpString, folderBeginMarker, folder, folderEndMarker];
        [tmpString release];
    }
    
    NSLog(@"File listing for folder: '%@' [ currentFolder = '%@' ]", folder, currentFolder);
    
    listString = @"";
    
    currentFolderCount = [self countSubstrings:currentFolder substring:folderEndMarker];
    
    for (i=0; i<j; i++) {
        
        name = [self examinePathName:[[idocs objectAtIndex:i] lastPathComponent] folderCount:&folderCount status:&status];
        
        if (status == NOT_IN_FOLDER)
            continue;
        
        isFolder = (status == IS_FOLDER);
        
        if (isFolder)
            nid = [NSString stringWithFormat:@"%d/%@", currentFolderCount + folderCount, name];
        else
            nid = name;
        
        if (k == 0)
            sep = @"";
        else
            sep = @", ";
        
        listString = [listString stringByAppendingFormat:@"%@{ isDir: %@, name: \"%@\", id: \"%@\" }", sep, (isFolder ? @"true" : @"false"), name, nid];
        k++;
    }
  
    // Update sketchometry's iCloud file listing ...
    
    [webview stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"GUI.Export.iCloud.listCallback({ response_data: [ %@ ] });", listString]];
    
    NSLog(@"[ %@ ]", listString);

    //[self iCloudDeleteFile:@"*"]; // Delete all iCloud documents
}

- (BOOL)iCloudUploadFile:(NSString*)fileName content:(NSString*)documentString
          allowOverwrite:(BOOL)allowOverwrite omitCallback:(BOOL)omitCallback
{
    NSURL *documentURL = [self documentURL:fileName];
    NSFileManager *fm = [NSFileManager defaultManager];
    
    if ([fm fileExistsAtPath:[documentURL path]]) {
        
        NSLog(@"File already exists at URL: %@", documentURL);
        
        if (allowOverwrite) {
            [fm removeItemAtPath:[documentURL path] error:nil];
            NSLog(@"Overwritting!");
        } else
            return FALSE;
    }
    
    [idocs addObject:documentURL];
    
    if (document)
        [document release];
    
    document = [[MyDocument alloc] initWithFileURL:documentURL];
    document.documentText = documentString;
    
    [document saveToURL:documentURL forSaveOperation:UIDocumentSaveForCreating completionHandler:nil];
    [document closeWithCompletionHandler:nil];
    
    if (!omitCallback)
        [webview stringByEvaluatingJavaScriptFromString:@"GUI.Export.iCloud.uploadCallback({ status: 200 });"];
    
    NSLog(@"Saved at URL: %@", documentURL.absoluteString);
    
    return TRUE;
}

- (void)iCloudDownloadFile:(NSString*)documentName
{
    NSURL *documentURL = [self documentURL:documentName];
    
    if (document)
        [document release];
    
    document = [[MyDocument alloc] initWithFileURL:documentURL];
    
    [document openWithCompletionHandler:^(BOOL success) {
 
        NSRegularExpression *regex;
        NSString *name, *pattern, *txt, *response;

        txt = @"GUI.Export.iCloud.downloadCallback({ status: ";

        if (success) {
            
            pattern = [NSString stringWithFormat:@".*%@", folderBeginMarker];
            regex = [NSRegularExpression regularExpressionWithPattern:pattern options:0 error:nil];
        
            name = [documentURL lastPathComponent];
            name = [regex stringByReplacingMatchesInString:name options:0 range:NSMakeRange(0, [name length]) withTemplate:@""];
            
            pattern = [NSString stringWithFormat:@".*%@", folderEndMarker];
            regex = [NSRegularExpression regularExpressionWithPattern:pattern options:0 error:nil];
            
            name = [regex stringByReplacingMatchesInString:name options:0 range:NSMakeRange(0, [name length]) withTemplate:@""];
            
            response = [NSString stringWithFormat:@"%@200, response_data: { name: '%@', content: '%@' }});", txt, name, document.documentText];
            
            NSLog(@"Loading succeeded!");
            
        } else {
            response = [NSString stringWithFormat:@"%@415, response_data: { name: '', content: '' }});", txt];
            
            NSLog(@"Loading failed!");
        }
        
        [webview stringByEvaluatingJavaScriptFromString:response];
        
    }];
    
    [document closeWithCompletionHandler:nil];
}

- (void)iCloudDeleteFile:(NSString*)documentName
{
    NSInteger i, j;
    
    NSFileManager *fm;
    NSURL *documentURL;
    
    j = [idocs count];
    
    NSLog(@"Trying to delete: %@ [ #iCloud files: %d ]", documentName, j);
    
    if ([documentName isEqualToString:@"*"]) {
        
        while ([idocs count] > 0)
            [self iCloudDeleteFile:[[[idocs objectAtIndex:0] absoluteString] lastPathComponent]];
        
    } else {
        
        documentURL = [self documentURL:documentName];
        
        for (i=0; i<j; i++)
            if ([[[idocs objectAtIndex:i] absoluteString] isEqualToString:[documentURL absoluteString]])
                break;
        
        if (i == j) {
            NSLog(@"Could not delete file %@ -- Not found!", documentName);
            return;
        }
        
        documentURL = [idocs objectAtIndex:i];
        [idocs removeObjectAtIndex:i];
        
        fm = [[NSFileManager alloc] init];
        [fm removeItemAtURL:documentURL error:nil];
        [fm release];
        
        NSLog(@"Deleted file %@ ...", documentName);
    }
}

- (void)iCloudCreateFolder:(NSString*)folder
{
    NSInteger status;
    NSString *response, *newFolder, *folderNid;
    
    newFolder = [NSString stringWithFormat:@"%@%@%@", folderBeginMarker, folder, folderEndMarker];
    folderNid = [NSString stringWithFormat:@"%d/%@", [self countSubstrings:currentFolder substring:folderEndMarker] + 1, folder];
    
    NSLog(@"Trying to create folder: %@ [ currentFolder = '%@' ]", folder, currentFolder);
    
    if ([self iCloudUploadFile:newFolder content:@"" allowOverwrite:FALSE omitCallback:TRUE]) {
        status = 200;
        NSLog(@"Folder creation was succesful!");
    } else {
        status = 415;
        NSLog(@"Folder creation failed!");
    }
    
    response = [NSString stringWithFormat:@"GUI.Export.iCloud.createCallback({ status: %d, response_data: { name: '%@', id: '%@' }});", status, folder, folderNid];
    [webview stringByEvaluatingJavaScriptFromString:response];
}

/********* List / Load / Save / Delete / Create -- END *********/

/*
 * UIWebViewDelegate protocol implementation
 **/

- (void)webViewDidStartLoad:(UIWebView *)webView
{
    NSLog(@"webView is loading ...");
}

- (void)webViewDidFinishLoad:(UIWebView *)webView
{
    [webView setHidden:FALSE];
    
    webView.scrollView.scrollEnabled = FALSE;
    
    [act stopAnimating];
    [act setHidden:TRUE];
    
    [splash setHidden:TRUE];
    
    [self iDocsInit];
    
    NSLog(@"Setting SKM language to iOS language ...");
    
    NSString *lang = [[NSLocale preferredLanguages] objectAtIndex:0], *jscript1 = @"for (var i=0; i<GUI.Lang.Map[0].length; i++) if (GUI.Lang.Map[0][i] == '",
        *jscript2 = @"') break; if (i < GUI.Lang.Map[0].length) GUI.Settings.set('language', GUI.Lang.Map[1][i]);";
    
    [webView stringByEvaluatingJavaScriptFromString:[NSString stringWithFormat:@"%@%@%@", jscript1, lang, jscript2]];
    
    // In the release version of Sketchometry the console.log's are disabled -- so they get re-enabled here ...
/*
    [webview stringByEvaluatingJavaScriptFromString:@"console.assert = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.debug = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.error = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.info = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.log = logToAppleApp;"];
    [webview stringByEvaluatingJavaScriptFromString:@"console.warn = logToAppleApp;"];
 */
}

- (BOOL)webView:(UIWebView *)webView shouldStartLoadWithRequest:(NSURLRequest *)request navigationType:(UIWebViewNavigationType)navigationType
{
    NSArray *requestArray;
    NSString *requestString;
    
    requestString = [[[request URL] absoluteString] stringByReplacingPercentEscapesUsingEncoding: NSUTF8StringEncoding];
    
    if ([(requestArray = [requestString componentsSeparatedByString:@":##sendToApp##"]) count] > 1) {
        
        [self webviewMsg:requestArray];
        
    } else if (navigationType == UIWebViewNavigationTypeLinkClicked) {
        
        [[UIApplication sharedApplication] openURL:[request URL]];
        
    } else if ([(requestArray = [requestString componentsSeparatedByString:@":##logToApp##"]) count] > 1) {
        
        NSLog(@"%@", [[requestArray objectAtIndex:0] lastPathComponent]);
        
    } else
        return YES;
    
    return NO;
}

@end