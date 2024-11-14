using System;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Amazon.Lambda.APIGatewayEvents;
using Amazon.Lambda.Core;
using Newtonsoft.Json;

[assembly: LambdaSerializer(typeof(Amazon.Lambda.Serialization.SystemTextJson.DefaultLambdaJsonSerializer))]

namespace EsepWebhook
{
    public class Function
    {
        private static readonly HttpClient httpClient = new HttpClient();

        public async Task<APIGatewayProxyResponse> FunctionHandler(APIGatewayProxyRequest request, ILambdaContext context)
        {
            try
            {
                dynamic json = JsonConvert.DeserializeObject<dynamic>(request.Body);
                string issueUrl = json.issue.html_url;

                string payload = $"{{'text':'Issue Created: {issueUrl}'}}";
                var content = new StringContent(payload, Encoding.UTF8, "application/json");

                var slackUrl = Environment.GetEnvironmentVariable("SLACK_URL");
                var response = await httpClient.PostAsync(slackUrl, content);

                return new APIGatewayProxyResponse
                {
                    StatusCode = 200,
                    Body = "Message sent to Slack"
                };
            }
            catch (Exception ex)
            {
                context.Logger.LogLine($"Error: {ex.Message}");
                return new APIGatewayProxyResponse
                {
                    StatusCode = 500,
                    Body = "Failed to process request"
                };
            }
        }
    }
}
