
% IoT Weather Station - Temperature Alert

% ThingSpeak Alerts API Key
alertApiKey = 'YOUR_ALERTS_API_KEY';

% Alerts API URL
alertUrl = "https://api.thingspeak.com/alerts/send";

% Configure API request
options = weboptions("HeaderFields", ...
    ["ThingSpeak-Alerts-API-Key", alertApiKey]);

% Email details
mailSubject = "IoT Weather Station: High Temperature Alert";

mailBody = "WARNING: Temperature has exceeded 35 degrees Celsius. Please check the weather conditions.";

% Send email
response = webwrite(alertUrl, ...
    "body", mailBody, ...
    "subject", mailSubject, options);

disp("Temperature alert email request accepted.");
