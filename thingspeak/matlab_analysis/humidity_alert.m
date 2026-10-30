
% IoT Weather Station - Humidity Alert

% ThingSpeak Alerts API Key
alertApiKey = 'YOUR_ALERTS_API_KEY';

% Alerts API URL
alertUrl = "https://api.thingspeak.com/alerts/send";

% Configure API request
options = weboptions("HeaderFields", ...
    ["ThingSpeak-Alerts-API-Key", alertApiKey]);

% Email details
mailSubject = "IoT Weather Station: High Humidity Alert";

mailBody = "WARNING: Relative humidity has exceeded 70 percent. Please check the weather conditions.";

% Send email
response = webwrite(alertUrl, ...
    "body", mailBody, ...
    "subject", mailSubject, options);

disp("Humidity alert email request accepted.");
