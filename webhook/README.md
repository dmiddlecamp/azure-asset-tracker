Setting up your Particle Webhook to Azure Service Bus
===

1.) Login to youre Azure portal:

    https://manage.windowsazure.com
    
2.) Setup a messaging Service Bus and remember the name, in this case we're using "sandbox-location1"

3.) It should automatically open the window for the new Service Bus.
Click on the connection Information button at the bottom, and copy out that connection string.

```
    Endpoint=sb://__YOUR_NAMESPACE__.servicebus.windows.net/;
    SharedAccessKeyName=RootManageSharedAccessKey;
    SharedAccessKey=__YOUR_SERVICE_BUS_KEY__
```

4.) Open up location.json, the example webhook configuration file.  Change the azure_sas_token key to your new key from
the info you found above.  Replace "YOUR_PROJECT_NAME" with the namespace of your Service Bus, in this case, 
"sandbox-location1".

5.) Create the webhook

```
    particle webhook create location.json
```

You should see something like this:

```
$ particle webhook create scratch.json 
Using settings from the file location.json
Sending webhook request  { uri: '/v1/webhooks',
  method: 'POST',
  json: 
   { event: 'GPS_coords',
     url: 'https://__YOUR_PROJECT_NAME__.servicebus.windows.net/weather/messages',
     deviceid: undefined,
     requestType: 'POST',
     mydevices: true,
     eventName: 'GPS_coords',
     json: 
      { latitude: '{{lat}}',
        longitude: '{{lon}}',
        altitude: '{{a}}',
        quality: '{{q}}',
        satellites: '{{s}}',
        battery_vcc: '{{vcc}}',
        battery_soc: '{{soc}}',
        published_at: '{{SPARK_PUBLISHED_AT}}',
        coreid: '{{SPARK_CORE_ID}}' },
     azure_sas_token: 
      { key_name: 'RootManageSharedAccessKey',
        key: '__YOUR_AZURE_KEY__' },
     nodefaults: true },
  headers: { Authorization: 'Bearer ABC123' } }
Successfully created webhook with ID DEF456

```

